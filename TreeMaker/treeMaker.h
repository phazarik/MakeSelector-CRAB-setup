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
  tree->Branch("lep1_sip3d",&lep1_sip3d,"lep1_sip3d/F",32000);
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

  tree->Branch("jec",           &jec,           "jec/F",           32000);
  tree->Branch("jer",           &jer,           "jer/F",           32000);

  // Weights:
  tree->Branch("gen_weight",      &gen_weight,       "gen_weight/D",        32000);
  tree->Branch("gen_weight_evt",  &gen_weight_evt,   "gen_weight_evt/D",    32000);
  tree->Branch("lumi_weight_evt", &lumi_weight_evt,   "lumi_weight_evt/D",   32000);
  
  // Nominal corrections:
  tree->Branch("wt_leptonSF",   &sf_lepIdIso,      "wt_leptonSF/D",       32000);
  tree->Branch("wt_trig",       &sf_lepTrigEff,    "wt_trig/D",           32000);
  tree->Branch("wt_pileup",     &sf_pileup,        "wt_pileup/D",         32000);
  tree->Branch("wt_bjet",       &sf_btagEff,       "wt_bjet/D",           32000);
  tree->Branch("wt_pdf",        &sf_pdf,           "wt_pdf/D",            32000);
  tree->Branch("wt_qcdscale",   &sf_qcdscale,      "wt_qcdscale/D",       32000);
  // Up variations:
  tree->Branch("wt_leptonSF_up",   &sf_lepIdIso_up,    "wt_leptonSF_up/D",    32000);
  tree->Branch("wt_trig_up",       &sf_lepTrigEff_up,  "wt_trig_up/D",        32000);
  tree->Branch("wt_pileup_up",     &sf_pileup_up,      "wt_pileup_up/D",      32000);
  tree->Branch("wt_bjet_up",       &sf_btagEff_up,     "wt_bjet_up/D",        32000);
  tree->Branch("wt_pdf_up",        &sf_pdf_up,         "wt_pdf_up/D",         32000);
  tree->Branch("wt_qcdscale_up",   &sf_qcdscale_up,    "wt_qcdscale_up/D",    32000);
  // Down variations:
  tree->Branch("wt_leptonSF_down", &sf_lepIdIso_down,  "wt_leptonSF_down/D",  32000);
  tree->Branch("wt_trig_down",     &sf_lepTrigEff_down,"wt_trig_down/D",      32000);
  tree->Branch("wt_pileup_down",   &sf_pileup_down,    "wt_pileup_down/D",    32000);
  tree->Branch("wt_bjet_down",     &sf_btagEff_down,   "wt_bjet_down/D",      32000);
  tree->Branch("wt_pdf_down",      &sf_pdf_down,       "wt_pdf_down/D",       32000);
  tree->Branch("wt_qcdscale_down", &sf_qcdscale_down,  "wt_qcdscale_down/D",  32000);
 
}

void AnaScript::FillTree(TTree *tree){
  
  // This function sets values to the variables that goes into the tree.
  bool basic_evt_selection = false;
  bool ee = false;
  bool em = false;
  bool me = false;
  bool mm = false;
  
  //Offline cuts on the leptons:
  float ptcut_mu  = 26;
  float ptcut_ele = 35; 
  if(_year==2016) {ptcut_ele = 30; ptcut_mu = 26;}
  if(_year==2017) {ptcut_ele = 37; ptcut_mu = 29;}

  bool evt_2LSS = false;
  bool evt_2LOS = false;

  //Baseline selection
  if((int)LightLepton.size()==2){

    //Check offline trigger:
    bool offline_trigger = false;
    for(int i=0; i<(int)LightLepton.size(); i++){
      int lepton_id = fabs(LightLepton.at(i).id);
      float lepton_pt = LightLepton.at(i).v.Pt();
      if(lepton_id == 11 && lepton_pt > ptcut_ele) offline_trigger = true;
      if(lepton_id == 13 && lepton_pt > ptcut_mu)  offline_trigger = true;
    }    
    if(LooseLepton.size() > 2) offline_trigger = false; //Veto additional loose leptons:

    //Check resonance-cut:
    bool reject_low_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 15;
    bool reject_most_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 150;

    //Check lepton charges:
    bool samesign = LightLepton.at(0).charge == LightLepton.at(1).charge;

    //Define events:
    if(offline_trigger && reject_low_resonances && samesign)   evt_2LSS = true; //2LSS
    if(offline_trigger && reject_most_resonances && !samesign) evt_2LOS = true; //2LOS

    //Veto additional events
    bool veto_3L4L_event = Veto3L4L();
    bool veto_HEM_event  = VetoHEM(Jet);
    bool veto_this_event = veto_3L4L_event || veto_HEM_event;
    if(veto_this_event){
      nEvtVeto++;
      evt_2LSS = false;
      evt_2LOS = false;
      return;
    }

    //------------------------------------------------//
    //                                                //
    //  SELECT FINAL-STATE HERE (ONLY ONE AT A TIME)  //
    //                                                //
    //------------------------------------------------//
    
    if(evt_2LOS){
      
      int flav0 = fabs(LightLepton.at(0).id);
      int flav1 = fabs(LightLepton.at(1).id);

      if(     flav0 == 13 && flav1 == 13){ mm = true; nevt_mm++; }
      else if(flav0 == 13 && flav1 == 11){ me = true; nevt_me++; }
      else if(flav0 == 11 && flav1 == 13){ em = true; nevt_em++; }
      else if(flav0 == 11 && flav1 == 11){ ee = true; nevt_ee++; }
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
  
  //-------------------------------------------
  // Select the channel :
  basic_evt_selection = mm || me || em || ee ;
  //-------------------------------------------

  if(basic_evt_selection){
    
    //-------------- EVENT WEIGHTS with systematic variations ------------------------
    sf_lepIdIso   = sf_lepIdIso_up   = sf_lepIdIso_down   = 1.0;
    sf_lepTrigEff = sf_lepTrigEff_up = sf_lepTrigEff_down = 1.0;
    sf_pileup     = sf_pileup_up     = sf_pileup_down     = 1.0;
    sf_btagEff    = sf_btagEff_up    = sf_btagEff_down    = 1.0;
    sf_pdf        = sf_pdf_up        = sf_pdf_down        = 1.0;
    sf_qcdscale   = sf_qcdscale_up   = sf_qcdscale_down   = 1.0;
    gen_weight_evt=1.0;
    
    if(_data==0){
      
      gen_weight = *Generator_weight;
      gen_weight_evt = *Generator_weight/avggenweight; //per_event
      lumi_weight_evt = lumiweight;                    //per_event
      //cout<<"Test: gen_weight_evt = "<<gen_weight_evt<<endl;
      
      auto safeSF = [](double sf){ return (sf<0) ? 1.0 : sf; }; //avoid negatives, just in case
      std::vector<std::string> modes = {"nom", "systup", "systdown"};

      for(const auto& mode: modes){
	double sf0 = safeSF(returnLeptonSF(LightLepton.at(0), mode));
	double sf1 = safeSF(returnLeptonSF(LightLepton.at(1), mode));
	double ef0 = GetLeptonTriggerEfficiency(LightLepton.at(0), mode);
	double ef1 = GetLeptonTriggerEfficiency(LightLepton.at(1), mode);
	double bSF = returnbJetCorrection(Jet, mode);
	double pu  = safeSF(returnPileUpWt(mode));
	double pdf = returnPDFweight(mode);
	double qcd = returnQCDscaleWeight(mode);
	if(mode=="nom"){
	  sf_lepIdIso   = sf0*sf1;
	  sf_lepTrigEff = 1-(1-ef0)*(1-ef1);
	  sf_btagEff    = bSF;
	  sf_pileup     = pu;
	  sf_pdf        = pdf;
	  sf_qcdscale   = qcd;
	}
	else if(mode=="systup"){
	  sf_lepIdIso_up   = sf0*sf1;
	  sf_lepTrigEff_up = 1-(1-ef0)*(1-ef1);
	  sf_btagEff_up    = bSF;
	  sf_pileup_up     = pu;
	  sf_pdf_up        = pdf;
	  sf_qcdscale_up   = qcd;
	}
	else if(mode=="systdown"){
	  sf_lepIdIso_down   = sf0*sf1;
	  sf_lepTrigEff_down = 1-(1-ef0)*(1-ef1);
	  sf_btagEff_down    = bSF;
	  sf_pileup_down     = pu;
	  sf_pdf_down        = pdf;
	  sf_qcdscale_down   = qcd;
	}
      }//modes
    }//MC    
    
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
