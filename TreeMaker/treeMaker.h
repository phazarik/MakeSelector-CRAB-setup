void AnaScript::InitializeBranches(TTree *tree){

  //Counts:
  tree->Branch("channel",   &channel,   "nchannel/I",  32000);
  tree->Branch("trigger",   &trigger,   "ntrigger/I",  32000);
  tree->Branch("nlep",      &nlep,      "nlep/I",      32000);
  tree->Branch("njet",      &njet,      "njet/I",      32000);
  tree->Branch("nfatjet",   &nfatjet,   "nfatjet/I",   32000);
  tree->Branch("nbjet",     &nbjet,     "nbjet/I",     32000);

  //Object-level (first lepton)
  tree->Branch("lep0_pt",   &lep0_pt,   "lep0_pt/F",   32000);
  tree->Branch("lep0_eta",  &lep0_eta,  "lep0_eta/F",  32000);
  tree->Branch("lep0_phi",  &lep0_phi,  "lep0_phi/F",  32000);
  tree->Branch("lep0_iso",  &lep0_iso,  "lep0_iso/F",  32000);
  tree->Branch("lep0_sip3d",&lep0_sip3d,"lep0_sip3d/F",32000);
  tree->Branch("lep0_mt",   &lep0_mt,   "lep0_mt/F",   32000);
  
  //Object-level (second lepton)
  tree->Branch("lep1_pt",   &lep1_pt,   "lep1_pt/F",   32000);
  tree->Branch("lep1_eta",  &lep1_eta,  "lep1_eta/F",  32000);
  tree->Branch("lep1_phi",  &lep1_phi,  "lep1_phi/F",  32000);
  tree->Branch("lep1_iso",  &lep1_iso,  "lep1_iso/F",  32000);
  tree->Branch("lep1_sip3d",&lep1_sip3d,"lep0_sip3d/F",32000);
  tree->Branch("lep1_mt",   &lep1_mt,   "lep1_mt/F",   32000);

  //Dilepton system:
  tree->Branch("dilep_pt",  &dilep_pt,  "dilep_pt/F",  32000);
  tree->Branch("dilep_eta", &dilep_eta, "dilep_eta/F", 32000);
  tree->Branch("dilep_phi", &dilep_phi, "dilep_phi/F", 32000);
  tree->Branch("dilep_mass",&dilep_mass,"dilep_mass/F",32000);
  tree->Branch("dilep_mt",  &dilep_mt,  "dilep_mt/F",  32000);
  tree->Branch("dilep_deta",   &dilep_deta,   "dilep_deta/F",   32000);
  tree->Branch("dilep_dphi",   &dilep_dphi,   "dilep_dphi/F",   32000);
  tree->Branch("dilep_dR",     &dilep_dR,     "dilep_dR/F",     32000);
  tree->Branch("dilep_ptratio",&dilep_ptratio,"dilep_ptratio/F",32000);

  //Event level:
  tree->Branch("LT",           &LT,           "LT/F",           32000);
  tree->Branch("LTplusMET",    &LTplusMET,    "LTplusMET/F",    32000);
  tree->Branch("HT",           &HT,           "HT/F",           32000);
  tree->Branch("HTfat",        &HTfat,        "HTfat/F",        32000);
  tree->Branch("HTplusMET",    &HTplusMET,    "HTplusMET/F",    32000);
  tree->Branch("HTfatplusMET", &HTfatplusMET, "HTfatplusMET/F", 32000);
  tree->Branch("STvis",        &STvis,        "STvis/F",        32000);
  tree->Branch("STvisfat",     &STvisfat,     "STvisfat/F",     32000);
  tree->Branch("ST",           &ST,           "ST/F",           32000);
  tree->Branch("STfat",        &STfat,        "STfat/F",        32000);
  tree->Branch("HTMETllpt",    &HTMETllpt,    "HTMETllpt/F",    32000);
  tree->Branch("HTfatMETllpt", &HTfatMETllpt, "HTfatMETllpt/F", 32000);
  tree->Branch("STfrac",       &STfrac,       "STfrac/F",       32000);
  tree->Branch("metpt",        &metpt_tree,   "metpt/F",        32000);
  tree->Branch("metphi",       &metphi_tree,  "metphi/F",       32000);

  tree->Branch("dphi_metlep0",   &dphi_metlep0,   "dphi_metlep0/F",   32000);
  tree->Branch("dphi_metlep1",   &dphi_metlep1,   "dphi_metlep1/F",   32000);
  tree->Branch("dphi_metdilep",  &dphi_metdilep,  "dphi_metdilep/F",  32000);
  tree->Branch("dphi_metlep_max",&dphi_metlep_max,"dphi_metlep_max/F",32000);
  tree->Branch("dphi_metlep_min",&dphi_metlep_min,"dphi_metlep_min/F",32000);

  //Corrections:
  tree->Branch("jec",           &jec,           "jec/F",           32000);
  tree->Branch("jer",           &jer,           "jer/F",           32000);
  tree->Branch("wt_leptonSF",   &sf_lepIdIso,   "sf_lepIdIso/D",   32000);
  tree->Branch("wt_trig",       &sf_lepTrigEff, "sf_lepTrigEff/D", 32000);
  tree->Branch("wt_pileup",     &wt_pileup,     "wt_pileup/D",     32000);
  tree->Branch("wt_bjet",       &sf_btagEff,    "sf_btagEff/D",    32000);
  tree->Branch("weight",        &event_weight,  "event_weight/D",  32000);
  // Up variations
  tree->Branch("wt_leptonSF_up",   &sf_lepIdIso_up,   "sf_lepIdIso_up/D",     32000);
  tree->Branch("wt_trig_up",       &sf_lepTrigEff_up, "sf_lepTrigEff_up/D",   32000);
  tree->Branch("wt_pileup_up",     &wt_pileup_up,     "wt_pileup_up/D",       32000);
  tree->Branch("wt_bjet_up",       &sf_btagEff_up,    "sf_btagEff_up/D",      32000);
  tree->Branch("weight_up",        &event_weight_up,  "event_weight_up/D",    32000);
  // Down variations
  tree->Branch("wt_leptonSF_down", &sf_lepIdIso_down, "sf_lepIdIso_down/D",   32000);
  tree->Branch("wt_trig_down",     &sf_lepTrigEff_down,"sf_lepTrigEff_down/D",32000);
  tree->Branch("wt_pileup_down",   &wt_pileup_down,   "wt_pileup_down/D",     32000);
  tree->Branch("wt_bjet_down",     &sf_btagEff_down,  "sf_btagEff_down/D",    32000);
  tree->Branch("weight_down",      &event_weight_down,"event_weight_down/D",  32000);
 
}

void AnaScript::FillTree(TTree *tree){
  
  // This function sets values to the variables that goes into the tree.
  bool basic_evt_selection = false;
  bool ee = false;
  bool em = false;
  bool me = false;
  bool mm = false;
  
  //Offline cuts on the leptons:
  float ptcut_mu  = 26; if(_year==2017) ptcut_mu  = 29;
  float ptcut_ele = 35; if(_year==2017) ptcut_ele = 37; if(_year==2016) ptcut_ele = 30;
  
  if(LightLepton.size() == 2){

    bool samesign = LightLepton.at(0).charge == LightLepton.at(1).charge;
    bool reject_low_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 15;
    bool reject_most_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 150;
    bool SS = samesign  && reject_low_resonances;
    bool OS = !samesign && reject_most_resonances;
    
    if(SS){
      
      int flav0 = fabs(LightLepton.at(0).id);
      int flav1 = fabs(LightLepton.at(1).id);

      //At least one of these two leptons must satisfy the offline trigger cut.
      bool offline_trigger = false;
      if(      flav0 == 13 && LightLepton.at(0).v.Pt() > ptcut_mu)  offline_trigger = true;
      else if (flav0 == 11 && LightLepton.at(0).v.Pt() > ptcut_ele) offline_trigger = true;
      if(      flav1 == 13 && LightLepton.at(1).v.Pt() > ptcut_mu)  offline_trigger = true;
      else if (flav1 == 11 && LightLepton.at(1).v.Pt() > ptcut_ele) offline_trigger = true;

      //Veto additional loose leptons:
      if(LooseLepton.size() > 2) offline_trigger = false;
      
      if(offline_trigger){
	if(     flav0 == 13 && flav1 == 13){ mm = true; }
	else if(flav0 == 13 && flav1 == 11){ me = true; }
	else if(flav0 == 11 && flav1 == 13){ em = true; }
	else if(flav0 == 11 && flav1 == 11){ ee = true; }
      }
    }
  }

  if(mm)      channel = (UInt_t)0;
  else if(me) channel = (UInt_t)1;
  else if(em) channel = (UInt_t)2;
  else if(ee) channel = (UInt_t)3;

  if(*HLT_SingleMuon==1 && *HLT_SingleEle==0)      trigger = (UInt_t)0; //Muon fires but not electron
  else if(*HLT_SingleMuon==0 && *HLT_SingleEle==1) trigger = (UInt_t)1; //Electron fires, but not muon
  else if(*HLT_SingleMuon==1 && *HLT_SingleEle==1) trigger = (UInt_t)2; //Both fire
  else if(*HLT_SingleMuon==0 && *HLT_SingleEle==0) trigger = (UInt_t)3; //None fire
  else cout<<"Something is wrong with triggers"<<endl;
  
  //#######################
  // Select the channel :
  //
  basic_evt_selection = mm || me || em || ee ;
  //
  //#######################

  if(basic_evt_selection){

    bool veto_3L4L_event = Veto3L4L();
    bool veto_HEM_event  = VetoHEM(Jet);
    bool veto_this_event = veto_3L4L_event || veto_HEM_event;
    if(veto_this_event){
      nEvtVeto++;
      return;
    }

    //Calculating event weights:
    double wt = 1.0;
    double lepIdIsoSF = 1.0, lepIdIsoSF_up = 1.0, lepIdIsoSF_down = 1.0;
    double triggerEff = 1.0, triggerEff_up = 1.0, triggerEff_down = 1.0;
    double pileupwt = 1.0,   pileupwt_up = 1.0,   pileupwt_down = 1.0;
    double bjetSF = 1.0,     bjetSF_up = 1.0,     bjetSF_down = 1.0;

    //Extracting SF from text files:
    if(_data==0){

      //Nominal weights:
      double sf0 = returnLeptonSF(LightLepton.at(0), "nom"); if(sf0<0) sf0=1.0;
      double sf1 = returnLeptonSF(LightLepton.at(1), "nom"); if(sf1<0) sf1=1.0;
      lepIdIsoSF = sf0*sf1;
      double ef0 = GetLeptonTriggerEfficiency(LightLepton.at(0), "nom"); 
      double ef1 = GetLeptonTriggerEfficiency(LightLepton.at(1), "nom");
      triggerEff = 1-((1-ef0)*(1-ef1));
      bjetSF = returnbJetCorrection(Jet, "nom"); if(bjetSF<1.0) bjetSF=1.0;
      pileupwt = returnPileUpWt("nom"); if(pileupwt<0) pileupwt=1.0;

      //Systematic up variations:
      double sf0_up = returnLeptonSF(LightLepton.at(0), "systup"); if(sf0_up<0) sf0_up=1.0;
      double sf1_up = returnLeptonSF(LightLepton.at(1), "systup"); if(sf1_up<0) sf1_up=1.0;
      lepIdIsoSF_up = sf0_up * sf1_up;
      double ef0_up = GetLeptonTriggerEfficiency(LightLepton.at(0), "systup"); 
      double ef1_up = GetLeptonTriggerEfficiency(LightLepton.at(1), "systup");
      triggerEff_up = 1-((1-ef0_up)*(1-ef1_up));
      bjetSF_up = returnbJetCorrection(Jet, "systup"); if(bjetSF_up<1.0) bjetSF_up=1.0;
      pileupwt_up = returnPileUpWt("systup"); if(pileupwt_up<0) pileupwt_up=1.0;
      
      //Systematic down variations:
      double sf0_down = returnLeptonSF(LightLepton.at(0), "systdown"); if(sf0_down<0) sf0_down=1.0;
      double sf1_down = returnLeptonSF(LightLepton.at(1), "systdown"); if(sf1_down<0) sf1_down=1.0;
      lepIdIsoSF_down = sf0_down * sf1_down;
      double ef0_down = GetLeptonTriggerEfficiency(LightLepton.at(0), "systdown"); 
      double ef1_down = GetLeptonTriggerEfficiency(LightLepton.at(1), "systdown");
      triggerEff_down = 1-((1-ef0_down)*(1-ef1_down));
      bjetSF_down = returnbJetCorrection(Jet, "systdown"); if(bjetSF_down<1.0) bjetSF_down=1.0;
      pileupwt_down = returnPileUpWt("systdown"); if(pileupwt_down<0) pileupwt_down=1.0;
      
    }
    
    //-------------------------
    // If some variables need 
    // corrections, do it here
    //-------------------------

    // Nominal weights:
    sf_lepIdIso   = lepIdIsoSF;
    sf_lepTrigEff = triggerEff;
    wt_pileup     = pileupwt;
    sf_btagEff    = bjetSF;
    event_weight  = lepIdIsoSF*triggerEff*pileupwt;

    // Up variations
    sf_lepIdIso_up   = lepIdIsoSF_up;
    sf_lepTrigEff_up = triggerEff_up;
    wt_pileup_up     = pileupwt_up;
    sf_btagEff_up    = bjetSF_up;
    event_weight_up  = lepIdIsoSF_up * triggerEff_up * pileupwt_up;

    // Down variations
    sf_lepIdIso_down   = lepIdIsoSF_down;
    sf_lepTrigEff_down = triggerEff_down;
    wt_pileup_down     = pileupwt_down;
    sf_btagEff_down    = bjetSF_down;
    event_weight_down  = lepIdIsoSF_down * triggerEff_down * pileupwt_down;
    
    //Integers:
    nlep    = (UInt_t)LightLepton.size();
    njet    = (UInt_t)Jet.size();
    nfatjet = (UInt_t)FatJet.size();
    nbjet   = (UInt_t)MediumbJet.size();
    
    //Object-level variables:
    lep0_pt  = (Float_t)LightLepton.at(0).v.Pt();
    lep0_eta = (Float_t)LightLepton.at(0).v.Eta();
    lep0_phi = (Float_t)LightLepton.at(0).v.Phi();
    lep0_iso = (Float_t)LightLepton.at(0).reliso03;
    lep0_sip3d = (Float_t)LightLepton.at(0).sip3d;
    lep0_mt  = (Float_t)transv_mass(LightLepton.at(0).v.E(), LightLepton.at(0).v.Phi(), metpt, metphi);
    lep1_pt  = (Float_t)LightLepton.at(1).v.Pt();
    lep1_eta = (Float_t)LightLepton.at(1).v.Eta();
    lep1_phi = (Float_t)LightLepton.at(1).v.Phi();
    lep1_iso = (Float_t)LightLepton.at(1).reliso03;
    lep1_sip3d = (Float_t)LightLepton.at(1).sip3d;
    lep1_mt  = (Float_t)transv_mass(LightLepton.at(1).v.E(), LightLepton.at(1).v.Phi(), metpt, metphi);

    //Dilepton system:
    TLorentzVector dilep = LightLepton.at(0).v + LightLepton.at(1).v;
    dilep_pt   = (Float_t)dilep.Pt();
    dilep_eta  = (Float_t)dilep.Eta();
    dilep_phi  = (Float_t)dilep.Phi();
    dilep_mass = (Float_t)dilep.M();
    dilep_mt   = (Float_t)transv_mass(dilep.E(), dilep.Phi(), metpt, metphi);
    dilep_deta    = (Float_t)fabs(LightLepton.at(0).v.Eta() - LightLepton.at(1).v.Eta());
    dilep_dphi    = (Float_t)delta_phi(LightLepton.at(0).v.Phi(), LightLepton.at(1).v.Phi());
    dilep_dR      = (Float_t)LightLepton.at(0).v.DeltaR(LightLepton.at(1).v);
    dilep_ptratio = (Float_t)lep1_pt/lep0_pt;

    //Event level:
    LT= LightLepton.at(0).v.Pt() + LightLepton.at(1).v.Pt();
    LTplusMET = LT + metpt;

    HT=0; for(Int_t i=0; i<(Int_t)Jet.size(); i++) HT = HT + Jet.at(i).v.Pt();
    HTfat=0; for(Int_t i=0; i<(Int_t)FatJet.size(); i++) HTfat = HTfat + FatJet.at(i).v.Pt();
    STvis = HT + LT;                   STvisfat = HTfat + LT;
    ST = HT + LT + metpt;              STfat = HTfat + LT + metpt;
    HTplusMET = HT + metpt;            HTfatplusMET = HTfat + metpt;
    HTMETllpt = HT + metpt + dilep_pt; HTfatMETllpt = HTfat + metpt + dilep_pt;
    STfrac = 0; if(ST>0) STfrac = dilep_pt/ST;
    dphi_metlep0    = (Float_t)delta_phi(LightLepton.at(0).v.Phi(), metphi);
    dphi_metlep1    = (Float_t)delta_phi(LightLepton.at(1).v.Phi(), metphi);
    dphi_metdilep   = (Float_t)delta_phi(dilep.Phi(), metphi);
    dphi_metlep_max = (Float_t)max(dphi_metlep0, dphi_metlep1);
    dphi_metlep_min = (Float_t)min(dphi_metlep0, dphi_metlep1);
    metpt_tree = metpt;
    metphi_tree = metphi;

    //---------------------------
    //Specific event selections:
    //---------------------------
    basic_evt_selection = basic_evt_selection && dilep_mass>15;
    bool baseline = basic_evt_selection;

    //---------------------------------------
    //Filling the tree with all these values:
    //Additional constraints can be put here.
    bool write_these_events = true;
    if(write_these_events){
      nEvtPass++;		   
      tree->Fill();
    }
    //---------------------------------------

  }//BasicEventSelection
}

//The following function is called to apply settings to all branches, if needed.
void AnaScript::AddAndCompressBranch(TBranch *br){
  br->SetBasketSize(17920);
  br->SetCompressionAlgorithm(2);
  br->SetCompressionLevel(9);
  br->SetCompressionSettings(209);
}
