#include<vector>
#include<TString.h>
#include "TRegexp.h"
using namespace std;

void AnaScript::ActivateBranch(TTree *t){
  //Option1:
  //t->SetBranchStatus("*", 1); //Keep all

  //Option2:
  //Common branches:
  vector<TString> branches = {"run","luminosityBlock","event",
			      "Flag_*",
			      "nMuon","Muon_*",
			      "nElectron","Electron_*",
			      "nJet","Jet_*",
			      "nFatJet","FatJet_*",
			      "MET_*","PuppiMET_*",
			      "*fixed*",
			      "HLT_IsoMu*", "HLT_Ele*WPTight_Gsf"};
  vector<TString> branches_mc = {"nGenPart","GenPart_*",
				 "nGenJet","GenJet_*",
				 //"nGenVisTau","GenVisTau_*",
				 "GenMET_phi","GenMET_pt",
				 //"*LHE*Weight*",//non-QCD only
				 "Pileup*"};
  if (_data == 0) branches.insert(branches.end(), branches_mc.begin(), branches_mc.end());

  cout<<"Keeping these branches:"<<endl;
  t->SetBranchStatus("*", 0); //Deactivate all and activate only the selected ones:
  for(auto activeBranchName : branches){
    cout<<" -"<<activeBranchName<<endl;
    t->SetBranchStatus(activeBranchName, 1);
  }
  cout<<endl;
}

void AnaScript::ReadBranch(){
  
  //Only the following branches will be filled.
  //The other branches (containing arrays of numbers) will be empty.
  //IF THE EMPTY BRANCHES ARE TO BE REMOVED, use the ActivateBranch function.
  //But this is risky, because all the branches used in the codes has to be mentioned there.
  //Otherwise it will lead to segmentation violation.
  
  *run;
  *luminosityBlock;
  *event;

  //HLT:
  *HLT_SingleMuon;
  *HLT_SingleEle;

  //Non-QCD:
  /*
  *LHEWeight_originalXWGTUP = {fReader_2022MC, "LHEWeight_originalXWGTUP"};
  *nLHEPdfWeight;for(unsigned int i=0; i<(unsigned int)*nLHEPdfWeight;i++){LHEPdfWeight[i];}
  *nLHEReweightingWeight;for(unsigned int i=0; i<(unsigned int)*nLHEReweightingWeight;i++){LHEReweightingWeight[i];}
  *nLHEScaleWeight; for(unsigned int i=0; i<(unsigned int)*nLHEScaleWeight;i++){LHEScaleWeight[i];}
  *nPSWeight; for(unsigned int i=0; i<(unsigned int)*nPSWeight;i++){PSWeight[i];}*/
  
  //Electron Branches:
  *nElectron;
  for(unsigned int i=0; i<(unsigned int)*nElectron;i++){
    Electron_dxy[i];
    Electron_dz[i];
    Electron_eta[i];
    Electron_mass[i];
    Electron_pfRelIso03_all[i];
    Electron_phi[i];
    Electron_pt[i];
    Electron_sip3d[i];
    Electron_charge[i];
    Electron_cutBased[i];
    Electron_pdgId[i];
    Electron_vidNestedWPBitmap[i];
    Electron_vidNestedWPBitmapHEEP[i];
    //Electron_jetIdx[i];
    Electron_tightCharge[i];
  }
  
  //Jets
  *nJet;
  for(unsigned int i=0; i<(unsigned int)*nJet;i++){
    Jet_area[i];
    Jet_btagDeepFlavB[i];
    Jet_chEmEF[i];
    Jet_chHEF[i];
    Jet_eta[i];
    Jet_mass[i];
    Jet_muEF[i];
    Jet_muonSubtrFactor[i];
    Jet_neEmEF[i];
    Jet_neHEF[i];
    Jet_phi[i];
    Jet_pt[i];
    Jet_electronIdx1[i];
    Jet_electronIdx2[i];
    Jet_jetId[i];
    Jet_muonIdx1[i];
    Jet_muonIdx2[i];
    Jet_nElectrons[i];
    Jet_nMuons[i];
    if(_data==0) Jet_hadronFlavour[i];
  }

  *nFatJet;
  for(unsigned int i=0; i<(unsigned int)*nJet;i++){
    FatJet_area[i];
    FatJet_eta[i];
    FatJet_mass[i];
    FatJet_phi[i];
    FatJet_pt[i];
    FatJet_jetId[i];
    if(_data==0) FatJet_hadronFlavour[i];
  }
  
  //PFMET
  *MET_MetUnclustEnUpDeltaX;
  *MET_MetUnclustEnUpDeltaY;
  *MET_covXX;
  *MET_covXY;
  *MET_covYY;
  *MET_phi;
  *MET_pt;
  *MET_significance;
  *MET_sumEt;
  *MET_sumPtUnclustered;

  //Muon Branches
  *nMuon;
  for(unsigned int i=0;i<(unsigned int)*nMuon;i++){
    Muon_dxy[i];
    Muon_dxyErr[i];
    Muon_dxybs[i];
    Muon_dz[i];
    Muon_dzErr[i];
    Muon_eta[i];
    Muon_ip3d[i];
    Muon_mass[i];
    Muon_miniPFRelIso_all[i];
    Muon_miniPFRelIso_chg[i];
    Muon_pfRelIso03_all[i];
    Muon_pfRelIso03_chg[i];
    Muon_pfRelIso04_all[i];
    Muon_phi[i];
    Muon_pt[i];
    Muon_ptErr[i];
    Muon_sip3d[i];
    Muon_charge[i];
    Muon_pdgId[i];
    Muon_highPtId[i];
    Muon_highPurity[i];
    Muon_inTimeMuon[i];
    Muon_isGlobal[i];
    Muon_isPFcand[i];
    Muon_isTracker[i];
    Muon_looseId[i];
    Muon_mediumId[i];
    Muon_mediumPromptId[i];
    Muon_tightCharge[i];
  }

  //PuppiMET
  *PuppiMET_phi;
  *PuppiMET_phiJERUp;
  *PuppiMET_phiJESUp;
  *PuppiMET_pt;
  *PuppiMET_ptJERUp;
  *PuppiMET_ptJESUp;
  *PuppiMET_sumEt;

  /*  
  //TrigObj
  *nTrigObj;
  for(unsigned int i=0; i<(unsigned int)*nTrigObj; i++){
    TrigObj_pt[i];
    TrigObj_eta[i];
    TrigObj_phi[i];
    TrigObj_l1pt[i];
    TrigObj_l1pt_2[i];
    TrigObj_l2pt[i];
    TrigObj_id[i];
    TrigObj_l1iso[i];
    TrigObj_l1charge[i];
    TrigObj_filterBits[i];
    }*/

  //Flags
  *Flag_HBHENoiseFilter;
  *Flag_HBHENoiseIsoFilter;
  *Flag_CSCTightHaloFilter;
  *Flag_CSCTightHaloTrkMuUnvetoFilter;
  *Flag_CSCTightHalo2015Filter;
  *Flag_globalTightHalo2016Filter;
  *Flag_globalSuperTightHalo2016Filter;
  *Flag_HcalStripHaloFilter;
  *Flag_hcalLaserEventFilter;
  *Flag_EcalDeadCellTriggerPrimitiveFilter;
  *Flag_EcalDeadCellBoundaryEnergyFilter;
  *Flag_ecalBadCalibFilter;
  *Flag_goodVertices;
  *Flag_eeBadScFilter;
  *Flag_ecalLaserCorrFilter;
  *Flag_trkPOGFilters;
  *Flag_chargedHadronTrackResolutionFilter;
  *Flag_muonBadTrackFilter;
  *Flag_BadChargedCandidateFilter;
  *Flag_BadPFMuonFilter;
  *Flag_BadPFMuonDzFilter;//
  *Flag_hfNoisyHitsFilter;//
  *Flag_BadChargedCandidateSummer16Filter;
  *Flag_BadPFMuonSummer16Filter;
  *Flag_trkPOG_manystripclus53X;
  *Flag_trkPOG_toomanystripclus53X;
  *Flag_trkPOG_logErrorTooManyClusters;
  *Flag_METFilters;
  /*
  //For Jet corrections: (Run3)
  *Rho_fixedGridRhoFastjetAll;
  *Rho_fixedGridRhoFastjetCentral;
  *Rho_fixedGridRhoFastjetCentralCalo;
  *Rho_fixedGridRhoFastjetCentralChargedPileUp;
  *Rho_fixedGridRhoFastjetCentralNeutral;
  */
  //For Jet corrections: (Run2)
  *fixedGridRhoFastjetAll;
  *fixedGridRhoFastjetCentral;
  *fixedGridRhoFastjetCentralCalo;
  *fixedGridRhoFastjetCentralChargedPileUp;
  *fixedGridRhoFastjetCentralNeutral;

  //Additionl HLT branches:
  //*HLT_Ele27_WPTight_Gsf;
  //*HLT_Ele28_WPTight_Gsf;
  //*HLT_Ele30_WPTight_Gsf;
  //*HLT_Ele32_WPTight_Gsf;
  //*HLT_Ele35_WPTight_Gsf;
  //*HLT_Ele38_WPTight_Gsf;
  //*HLT_Ele40_WPTight_Gsf;
  //*HLT_IsoMu20;
  //*HLT_IsoMu24;
  //*HLT_IsoMu24_eta2p1;
  //*HLT_IsoMu27;

  //for MC:
  if(_data==0){

    *Generator_weight;
    *GenMET_phi;
    *GenMET_pt;
    
    *nGenPart;
    for(unsigned int i=0; i<(unsigned int)*nGenPart; i++){
      GenPart_eta[i];
      GenPart_mass[i];
      GenPart_phi[i];
      GenPart_pt[i];
      GenPart_genPartIdxMother[i];
      GenPart_pdgId[i];
      GenPart_status[i];
    }
    
    *nGenJet;
    for(unsigned int i=0; i<(unsigned int)*nGenPart; i++){
      GenJet_eta[i];
      GenJet_mass[i];
      GenJet_phi[i];
      GenJet_pt[i];
    }
    
    *Pileup_nPU;
    *Pileup_sumEOOT;
    *Pileup_sumLOOT;
    *Pileup_nTrueInt;
    *Pileup_gpudensity;
  }
  
}
