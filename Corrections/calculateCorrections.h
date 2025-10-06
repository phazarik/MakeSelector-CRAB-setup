#include "loadCorrectionsFromPOG.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_2016preVFP_UL.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_2016postVFP_UL.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_2017_UL.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_2018_UL.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_Run3Summer22.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_Run3Summer22EE.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_Run3Summer23.h"
#include "bTaggingSF/JetEff_DeepJet_MediumWP_Run3Summer23BPix.h"
#include "TRandom3.h"

double AnaScript::returnLeptonSF(Particle lepton, TString mode){
  int id = fabs(lepton.id);
  double sf = 1.0;
  
  if(id == 11)      sf = returnElectronIDSF(lepton, mode);
  else if(id == 13) {
    if(lepton.v.Pt()<15) return 1.0;
    else sf = returnMuonIDSF(lepton, mode)*returnMuonIsoSF(lepton, mode);
  }
  return sf;
}

//----------------------------
// Jet resolution corrections
//----------------------------
double AnaScript::returnJetResolutionCorrection(Particle jet, TString mode){

  float pt = jet.v.Pt();
  float eta = jet.v.Eta();
  
  double sjer = returnJetJERSF(jet, mode);
  double sigmajer = returnJetPtResSF(jet);
  double cjer     = 1.0; //This is the correction to jets.

  //Matching with the nearest gen-jet:
  bool isGenMatched = false;
  int closest_index = -1;
  float mindR = 1000;
  float genpt = -1;

  //dR minimization:
  for(int i=0; i<(int)genJet.size(); i++){
    float tempdR = jet.v.DeltaR(genJet.at(i).v);
    if(tempdR < mindR){
      closest_index = i;
      mindR = tempdR;
      genpt = genJet.at(i).v.Pt();
    }
  }
  if(mindR<0.2 && (abs(pt - genpt)<(3*pt*sigmajer))) isGenMatched=true;
  
  //Calculation of cjer based on gen-matching:
  //Hybrid method(Usual scaling + stochastic scaling)
  if(isGenMatched){
    cjer = 1.+(sjer-1.)*((pt-genpt)/pt);
  }
  else{
    TRandom3* gRandom = new TRandom3();
    gRandom->SetSeed(0);
    float n = gRandom->Gaus( 0., sigmajer );
    cjer = 1.+n*(sqrt(max( sjer*sjer-1., 0. )));
  }
  if(cjer<0.){cjer=0.;} //cjer is truncated at zero as required

  return cjer;

}

//--------------------------
// bJet tagging corrections
//--------------------------
double AnaScript::returnbJetCorrection(vector<Particle> Jet, TString mode){

  //-----------------------------------------------------------------------------------------------------------
  // Method used: 1a) Event reweighting using scale factors and MC b-tagging efficiencies
  // tWiki link: https://twiki.cern.ch/twiki/bin/viewauth/CMS/BTagSFMethods
  //-----------------------------------------------------------------------------------------------------------

  double probability_mc   = 1.0;
  double probability_data = 1.0;

  //For each Jet,  
  for (int i = 0; i < (int)Jet.size(); i++){

    double jet_mceff     = 1.0;
    double jet_prob_mc   = 1.0;
    double jet_prob_data = 1.0;
    
    // 1) Extract the MC efficiency.
    if(_campaign=="2016postVFP_UL")        jet_mceff = (double)btagMCeff_2016postVFP_UL(Jet.at(i));
    else if(_campaign=="2016preVFP_UL")    jet_mceff = (double)btagMCeff_2016preVFP_UL(Jet.at(i));    
    else if(_campaign=="2017_UL")          jet_mceff = (double)btagMCeff_2017_UL(Jet.at(i));
    else if(_campaign=="2018_UL")          jet_mceff = (double)btagMCeff_2018_UL(Jet.at(i));
    else if(_campaign=="Run3Summer22")     jet_mceff = (double)btagMCeff_Run3Summer22(Jet.at(i));
    else if(_campaign=="Run3Summer22EE")   jet_mceff = (double)btagMCeff_Run3Summer22EE(Jet.at(i));
    else if(_campaign=="Run3Summer23")     jet_mceff = (double)btagMCeff_Run3Summer23(Jet.at(i));
    else if(_campaign=="Run3Summer23BPix") jet_mceff = (double)btagMCeff_Run3Summer23BPix(Jet.at(i));
    else return 1.0;
    //else cout<<"btv_deepjet.h : Provide correct btag SF file!"<<endl;
    //cout<<"\nTest: bJet MC eff = "<<jet_mceff<<endl;
   
    // 2) Extract the SF from POG.
    double SFfromPOG = returnbJetTaggingSFPOG(Jet.at(i), mode);
    //cout<<"Test: bJet SF (POG) = "<<SFfromPOG<<endl;
    
    // 3) Pick a working point.
    double WPth = _btagWP;

    // 4) Check if the jet is tagged or not,
    //    and calculate probability for the jet being tagged/not tagged.
    //    The probability for data is scaled using the SF from POG.
    if (Jet.at(i).btagscore > WPth){
      jet_prob_data = jet_mceff*SFfromPOG;
      jet_prob_mc   = jet_mceff;
    }
    else {    
      jet_prob_data = 1-(jet_mceff*SFfromPOG);
      jet_prob_mc   = 1-jet_mceff;
    }
    
    // 5) Combine the probability of each jet to the event-configuration..
    probability_data *= jet_prob_data;
    probability_mc   *= jet_prob_mc;

  }//Jet loop ends.

  // 6) The scale factor comes from the difference between data and MC probability for the jet configuration.
  double scaleFactor = 1.0;
  if (probability_mc > 0.0) scaleFactor = probability_data/probability_mc;
  //cout << "Test: bJet SF = "<<scaleFactor <<endl;

  return scaleFactor;

}
