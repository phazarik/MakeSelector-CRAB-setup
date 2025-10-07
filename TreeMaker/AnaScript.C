#define AnaScript_cxx
#include "AnaScript.h"
#include <TH2.h>
#include <TStyle.h>

//Additional headers:
#include "../includeHeaders.h"
#include "../Setup/json_setup.h"
#include "../Corrections/calculateCorrections.h"
#include "../Corrections/TriggerEfficiency.h"
#include "treeMaker.h"

void AnaScript::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}
void AnaScript::SlaveBegin(TTree *tree)
{
  TString option = GetOption();
  time(&start);

  //Set year and btagWP:
  if      (_campaign =="2016postVFP_UL")    {_year=2016; _btagWP=0.2489;}
  else if (_campaign =="2016preVFP_UL")     {_year=2016; _btagWP=0.2598;}
  else if (_campaign =="2017_UL")           {_year=2017; _btagWP=0.3040;}
  else if (_campaign =="2018_UL")           {_year=2018; _btagWP=0.2783;}
  else if (_campaign == "Run3Summer22")     {_year=2022; _btagWP=0.3086;}
  else if (_campaign == "Run3Summer22EE")   {_year=2022; _btagWP=0.3196;}
  else if (_campaign == "Run3Summer23")     {_year=2023; _btagWP=0.2431;}
  else if (_campaign == "Run3Summer23BPix") {_year=2023; _btagWP=0.2435;}
  else cout<<"main: Provide correct campaign name!"<<endl;
  //Source: https://btv-wiki.docs.cern.ch/ScaleFactors/
  
  cout<<"\nParameters:"<<endl;
  cout<<"Campaign = "<< _campaign <<endl;
  cout<<"Year   = "  << _year <<endl;
  cout<<"Sample = "  << _samplename <<endl;
  cout<<"Flag   = "  << _flag <<endl;
  cout<<"btagWP = "  << _btagWP <<endl;
  cout<<"Data   = "  << _data <<"\n"<<endl;

  //Initializing counters:
  nEvtGen=tree->GetEntries();
  nEvtTotal=0; nEvtRan=0;  nEvtTrigger=0;
  nEvtPass=0;  nEvtBad=0;  nThrown=0; nEvtVeto=0;

  //For Skimmer:
  //tree->SetBranchStatus("*",0);
  //ActivateBranch(tree);

  //For TreeMaker: Loading offline data (json, text):
  jsondata = loadJson();
  LoadCorrectionsFromPOG();

  /*
  //Debugging json files:
  cout << "Reading from pileupwtPOG"<< endl;
  cout << "Number of entries : " << pileupwtPOG.size() << endl;
  int count = 0;
  for (const auto &entry : pileupwtPOG) {
    cout << entry.campaign << " " << entry.ntrueInt << " " << entry.sf<<endl;
    if (++count >= 5) break;
    }*/

  bad_event = false;
  evt_trigger = false;

  cout << "\n"
     << right << setw(8) << "Progress"
     << right << setw(12) << "nEvents"
     << right << setw(8) << "Time" << endl;

}
void AnaScript::SlaveTerminate()
{
  //For TreeMaker:
  //_TreeFile->cd();
  //_mytree->Write("", TObject::kOverwrite);
  //_TreeFile->Close();
  if (_mytree) _mytree->AutoSave("SaveSelf");
  
  float goodevtfrac = ((float)nEvtRan)/((float)nEvtTotal);
  float trigevtfrac = ((float)nEvtTrigger)/((float)nEvtTotal);
  float passevtfrac = ((float)nEvtPass)/((float)nEvtTotal);
  float badevtfrac  = ((float)nEvtBad)/((float)nEvtTotal);//for VLLD
  float notgoldenevtfrac  = ((float)nThrown)/((float)nEvtTotal);

  cout<<"---------------------------------------------"<<endl;
  cout<<"Summary:"<<fixed << setprecision(6)<<endl;
  cout<<"nEvtTotal = "<<nEvtTotal<<endl;
  cout<<"nEvtRan = "<<nEvtRan<<" ("<<goodevtfrac*100<<" %)"<<endl;
  cout<<"nEvtTrigger = "<<nEvtTrigger<<" ("<<trigevtfrac*100<<" %)"<<endl;
  cout<<"nEvtPass = "<<nEvtPass<<" ("<<passevtfrac*100<<" %)"<<endl;
  cout<<"nEvtBad = "<<nEvtBad<<" ("<<badevtfrac*100<<" %)"<<endl;
  cout<<"nEvtVeto = "<<nEvtVeto<<endl;
  if(_data!=0) cout<<"nEvents not in golden json = "<<nThrown<<" ("<<notgoldenevtfrac*100<<" %)"<<endl;
  cout<<"---------------------------------------------"<<endl;

  time(&end);
  double time_taken = double(end-start);
  cout<<"\nTime taken by the programe is= "<<fixed<<time_taken<<setprecision(5);
  cout<<" sec \n"<<endl;
  cout << "Final tree entries: " << _mytree->GetEntries() << endl;
}
void AnaScript::Terminate()
{
  if (_TreeFile && _mytree) {
    _TreeFile->cd();
    _mytree->Write("", TObject::kOverwrite);
    _TreeFile->Close();
    delete _TreeFile;
    _TreeFile = nullptr;
    _mytree = nullptr;
  }
}

Bool_t AnaScript::Process(Long64_t entry)
{
  nEvtTotal++;

  //Initializing fReaders:
  fReader                .SetLocalEntry(entry);
  if(_data==0) fReader_MC.SetLocalEntry(entry);

  //Setting verbosity:
  if (nEvtTotal % 10000 == 0) {
    time(&buffer);
    double time_buff = double(buffer-start);
    double frac = (double)nEvtTotal / nEvtGen * 100.0;
    string progress = (ostringstream() << fixed << setprecision(2) << frac << "%").str();
    cout << right << setw(8) << progress
	 << right << setw(12) << nEvtTotal
	 << right << setw(8) << fixed << setprecision(0) << time_buff <<endl;
  }
  
  //Filtering bad events:
  bool common  = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter &&
    *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter;
  bool eeBadSc = _data ? *Flag_eeBadScFilter : 1;

  //GoodEvt2018 = (_year == 2018 ? common && eeBadSc && *Flag_BadPFMuonDzFilter && *Flag_ecalBadCalibFilter : 1);
  //GoodEvt2017 = (_year == 2017 ? common && eeBadSc && *Flag_BadPFMuonDzFilter : 1);
  GoodEvt2018 = (_year == 2018 ? common && eeBadSc && *Flag_ecalBadCalibFilter : 1);
  GoodEvt2017 = (_year == 2017 ? common && eeBadSc : 1);
  GoodEvt2016 = (_year == 2016 ? common && eeBadSc : 1);
  GoodEvt2022 = (_year == 2022 ? common && eeBadSc : 1);
  GoodEvt2023 = (_year == 2022 ? common && eeBadSc : 1);
  GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016 && GoodEvt2022 && GoodEvt2023;

  if(GoodEvt){
    nEvtRan++;

    triggerRes         = true; //default, always true for MC
    muon_trigger       = *HLT_SingleMuon;
    electron_trigger   = *HLT_SingleEle;
    overlapping_events = muon_trigger && electron_trigger;

    if(_data !=0){
      //Applying trigger on data:
      if(_flag == "muon")   triggerRes = muon_trigger; //For the SingleMuon dataset, including overlap.
      if(_flag == "egamma") triggerRes = electron_trigger && !muon_trigger; //For the EGamma dataset

      //Throw awaying bad data that are not included in the GoldenJson:
      int runno = (int)*run;
      int lumisection = (int)*luminosityBlock;
      bool golden_event = checkJson(true, runno, lumisection);
      if(!golden_event){
	nThrown++;
	triggerRes = false;
      }
    }//Applying trigger on data

    if(triggerRes){
      nEvtTrigger++;

      //----------------------------------------------------------------------------------------------------------
      // OBJECT DEFINITIONS
      //----------------------------------------------------------------------------------------------------------

      //----------------
      // Gen-Particles
      //----------------
      genMuon.clear();  genElectron.clear();  genLightLepton.clear();
      genJet.clear();   vllep.clear();        vlnu.clear();

      //Handling bad events from signal:
      bad_event = false;

      if(_data==0){
	createGenLightLeptons();
	createGenJets();
        SortGenObjects();
	//SortPt(genMuon);
	//SortPt(genElectron);
	//SortPt(genLightLepton);
	createSignalArrays();
	SortVLL();

	//Correcting the Doublet model (flagging out the invalid decays)
	if(_flag=="doublet"){ //for VLLD files
	  bad_event = false;
	  //a) The neutral particle cannot decay to H,nu or Z,nu.
	  // I am flagging out the events with Higgs(25) or the Z(23) as daughetrs of N
	  //cout<<"----"<<endl;
	  for(int i=0; i<(int)vlnu.size(); i++){
	    for(int j=0; j<(int)vlnu.at(i).dauid.size(); j++){
	      if(fabs(vlnu.at(i).dauid[j]) == 25)      bad_event = true;
	      else if(fabs(vlnu.at(i).dauid[j]) == 23) bad_event = true;
	      //cout<<fabs(vlnu.at(i).dauid[j])<<" ";
	    }
	    //cout<<""<<endl;
	  }
	  //if(bad_event) cout<<"bad"<<endl;
	  //else cout<<"good"<<endl;
	  //cout<<"----"<<endl;
	  
	  //b) The lepton cannot decay to a W,nu of the corresponding flavor (ele/mu):
	  // I am flagging out the events with W(24) as daughetrs of L
	  for(int i=0; i<(int)vllep.size(); i++){
	    for(int j=0; j<(int)vllep.at(i).dauid.size(); j++){
	      if(fabs(vllep.at(i).dauid[j]) == 24)     bad_event = true;
	    }
	  }
	}
	//Make gen-level plots here.
      }
      //Counting bad events:
      if(bad_event) nEvtBad++;

      //----------------
      // Reco-Particles
      //----------------
      
      metpt = *PuppiMET_pt;
      metphi = *PuppiMET_phi;
      
      Muon.clear();    Electron.clear();          LightLepton.clear();
      Photon.clear();  Tau.clear();               Jet.clear();
      bJet.clear();    MediumbJet.clear();        FatJet.clear();
      LooseLepton.clear(); LooseElectron.clear(); LooseMuon.clear();
      
      createLightLeptons();
      //createTaus();
      createJets();
      createFatJets();
      SortRecoObjects();

      //-------------------------------------------------
      //Corrections to Jets: (needs to be done only once)
      //-------------------------------------------------
      jec = 1.0;
      jer = 1.0;
      if(_data == 0){
	for(int i=0; i<(int)Jet.size(); i++){
	  jec =  returnJetJECSF(Jet.at(i), "nom");
	  jer =  returnJetResolutionCorrection(Jet.at(i), "nom");
	  Jet.at(i).v = Jet.at(i).v * jec;
	  Jet.at(i).v = Jet.at(i).v * jer;
	}
      }

      //----------------------------------------------------------------------------------------------------------
      // Writing to tree
      //----------------------------------------------------------------------------------------------------------
      
      if(!bad_event) FillTree(_mytree);     
      
    }//Triggered Events
  }//GoodEvt
  return kTRUE;
}
