using namespace std;

void AnaScript::ActivateBranch(TTree *t){
  t->SetBranchStatus("*", 1); //Keep all
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

  //HLT;
  *HLT_SingleMuon;
  *HLT_SingleEle;
  
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
  }

  //PuppiMET
  *PuppiMET_phi;
  *PuppiMET_phiJERUp;
  *PuppiMET_phiJESUp;
  *PuppiMET_pt;
  *PuppiMET_ptJERUp;
  *PuppiMET_ptJESUp;
  *PuppiMET_sumEt;
  
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
  }

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
  //*Flag_BadPFMuonDzFilter;
  //*Flag_hfNoisyHitsFilter;
  *Flag_BadChargedCandidateSummer16Filter;
  *Flag_BadPFMuonSummer16Filter;
  *Flag_trkPOG_manystripclus53X;
  *Flag_trkPOG_toomanystripclus53X;
  *Flag_trkPOG_logErrorTooManyClusters;
  *Flag_METFilters;

  //For Jet corrections: (Run3)
  *Rho_fixedGridRhoFastjetAll;
  *Rho_fixedGridRhoFastjetCentral;
  *Rho_fixedGridRhoFastjetCentralCalo;
  *Rho_fixedGridRhoFastjetCentralChargedPileUp;
  *Rho_fixedGridRhoFastjetCentralNeutral;

  if(_data==0){
    *Pileup_nPU;
    *Pileup_sumEOOT;
    *Pileup_sumLOOT;
    *Pileup_nTrueInt;
    *Pileup_gpudensity;
  }

  *HLT_Ele27_WPTight_Gsf;
  *HLT_Ele28_WPTight_Gsf;
  *HLT_Ele30_WPTight_Gsf;
  *HLT_Ele32_WPTight_Gsf;
  *HLT_Ele35_WPTight_Gsf;
  *HLT_Ele38_WPTight_Gsf;
  *HLT_Ele40_WPTight_Gsf;
  *HLT_IsoMu20;
  *HLT_IsoMu24;
  *HLT_IsoMu24_eta2p1;
  *HLT_IsoMu27;
  //*HLT_IsoMu30;
  //*HLT_Mu12;
  *HLT_Mu15;
  *HLT_Mu20;
  *HLT_Mu27;
  *HLT_Mu50;
  *HLT_Mu55;
  
}
