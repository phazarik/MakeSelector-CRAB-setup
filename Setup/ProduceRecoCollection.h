//################
// Light Leptons :
//################

void AnaScript::createLightLeptons(){

  //Muon block:
  //unsigned int iterator_mu = (unsigned int)*(readerConfig->nMuon);
  unsigned int iterator_mu = (unsigned int)*nMuon;
  for(unsigned int i=0; i<iterator_mu ; i++){;
    Particle temp;
    temp.v.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],0.105);
    temp.id = -13*Muon_charge[i];
    temp.ind = i;
    temp.charge = Muon_charge[i];
    temp.sip3d  = Muon_sip3d[i];
    temp.reliso03 = Muon_pfRelIso03_all[i];
    temp.reliso04 = Muon_pfRelIso04_all[i];
    temp.genindex = -1;
    temp.hovere   = -999;
    temp.r9       = -999;
    
    bool ptetacut = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4; //warning
    bool promptmuon = fabs(Muon_dxy[i])<0.05 && fabs(Muon_dz[i])<0.1;
    bool passcut_loosemuon  = ptetacut && promptmuon && Muon_looseId[i] &&  Muon_pfRelIso03_all[i]<1.00;
    bool passcut_mediummuon = ptetacut && promptmuon && Muon_mediumId[i] && Muon_pfRelIso03_all[i]<0.15; //warning

    if(passcut_mediummuon){
      Muon.push_back(temp);
      LightLepton.push_back(temp);
    }
    if(passcut_loosemuon){
      LooseLepton.push_back(temp);
      LooseMuon.push_back(temp);
    }
  }//for muons

  //Electron block:
  //unsigned int iterator_ele = (unsigned int)*(readerConfig->nElectron);
  unsigned int iterator_ele = (unsigned int)*nElectron;
  for(unsigned int i=0; i<iterator_ele; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],0.000511); 
    temp.id = -11*Electron_charge[i];
    temp.ind = i;
    temp.charge   = Electron_charge[i];
    temp.sip3d    = Electron_sip3d[i];
    temp.reliso03 = Electron_pfRelIso03_all[i];
    temp.genindex = -1;
    temp.hovere   = Electron_hoe[i];
    temp.r9       = Electron_r9[i];

    bool ptetacut = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4; //warning
    bool cleaned_from_muons = clean_from_array(temp, LooseMuon, 0.05);
    bool isprompt = false;
    if(fabs(temp.v.Eta())<=1.479){//for barrel
      if(fabs(Electron_dxy[i])<0.05 && fabs(Electron_dz[i])<0.1)
	isprompt = true;
    }
    if(fabs(temp.v.Eta())>1.479){//endcap
      if(fabs(Electron_dxy[i])<0.1 && fabs(Electron_dz[i])<0.2)
	isprompt = true;
    }
    bool passcut_looseele  = ptetacut && isprompt && (int)Electron_cutBased[i]>1 && Electron_pfRelIso03_all[i] < 1.0;
    bool passcut_mediumele = ptetacut && isprompt && (int)Electron_cutBased[i]>2 && cleaned_from_muons && Electron_pfRelIso03_all[i] < 0.15; //warning

    if(passcut_mediumele){
      Electron.push_back(temp);
      LightLepton.push_back(temp);
    }
    if(passcut_looseele){
      LooseLepton.push_back(temp);
      LooseElectron.push_back(temp);
    }
  }//For electrons
  
} 

//_____________________________________________________________________
/*
void AnaScript::createPhotons(){
  for(unsigned int i=0; i<(unsigned int)*nPhoton; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(Photon_pt[i],Photon_eta[i],Photon_phi[i],0); 
    temp.id = 22*Photon_charge[i];
    temp.ind = i;
    temp.reliso03 = Photon_pfRelIso03_all[i];
    temp.genindex = -1;

    bool ptetacut = temp.v.Pt()>50 && temp.v.Eta()<2.4;
    bool passcuts = ptetacut && Photon_pfRelIso03_all[i]<0.15;
    if(passcuts) Photon.push_back(temp);
  }
  }

//_____________________________________________________________________

void AnaScript::createTaus(){
  //unsigned int iterator = (unsigned int)*(readerConfig->nTau);
  unsigned int iterator_tau = (unsigned int)*nTau;
  for(unsigned int i=0; i<iterator_tau ; i++){
    //Set the energy corrections according the decay modes:
    float tlv_corr = 1.;
    if(_year==2016){
      if(Tau_decayMode[i]==0)  tlv_corr = 0.994;
      if(Tau_decayMode[i]==1)  tlv_corr = 0.995;
      if(Tau_decayMode[i]>9)   tlv_corr = 1;
    }
    if(_year==2017){
      if(Tau_decayMode[i]==0)  tlv_corr = 1.007;
      if(Tau_decayMode[i]==1)  tlv_corr = 0.998;
      if(Tau_decayMode[i]==10) tlv_corr = 1.001;
      if(Tau_decayMode[i]==11) tlv_corr = 0.999;
    }
    if(_year==2018){
      if(Tau_decayMode[i]==0)  tlv_corr = 0.987;
      if(Tau_decayMode[i]==1)  tlv_corr = 0.995;
      if(Tau_decayMode[i]==10) tlv_corr = 0.998;
      if(Tau_decayMode[i]==11) tlv_corr = 1;
    }

    Particle temp;
    temp.v.SetPtEtaPhiM(Tau_pt[i],Tau_eta[i],Tau_phi[i],1.77);
    temp.v *= tlv_corr; //energy correction
    temp.id = -15*Tau_charge[i];
    temp.ind = i;
    temp.charge = Tau_charge[i];
    temp.genindex = -1;

    bool ptetacut = temp.v.Pt()>20 && fabs(temp.v.Eta())<2.3;
    bool cleaned_from_leptons = clean_from_array(temp, LooseLepton, 0.5);
    bool DeepTauID= Tau_idDeepTau2017v2p1VSe[i]>15 && Tau_idDeepTau2017v2p1VSmu[i]>3 && Tau_idDeepTau2017v2p1VSjet[i]>127;
    bool passcut = ptetacut && DeepTauID && cleaned_from_leptons && fabs(Tau_dz[i]<0.2);

    if(passcut) Tau.push_back(temp);

  }
}
*/
//_____________________________________________________________________

void AnaScript::createJets(){
  unsigned int iterator_jet = (unsigned int)*nJet;
  for(unsigned int i=0; i<iterator_jet; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(Jet_pt[i],Jet_eta[i],Jet_phi[i],Jet_mass[i]);
    temp.ind = i;
    temp.btagscore = Jet_btagDeepFlavB[i];
    temp.hadronflavor = -1;
    if(_data==0) temp.hadronflavor = (int)Jet_hadronFlavour[i];

    bool ptetacut = temp.v.Pt()>50 && fabs(temp.v.Eta())<2.4; //warning
    bool cleaned_from_leptons = clean_from_array(temp, LooseLepton, 0.4);
    //bool cleaned_from_muons = clean_from_array(temp, Muon, 0.4);
    //bool cleaned_from_taus = clean_from_array(temp, Tau, 0.5);
    bool jetID = _year == 2016 ? (int)Jet_jetId[i]>=1 : (int)Jet_jetId[i]>=2; //if 2016, >=1; else >=2
    bool passcut = ptetacut && cleaned_from_leptons && jetID;
    //bool passcut = ptetacut && jetID; //warning

    //Btagging thresholds:
    //Source: https://btv-wiki.docs.cern.ch/ScaleFactors/
    float WPth=0;
    if(_campaign =="2018_UL")                 WPth=0.2783;
    else if (_campaign =="2017_UL")           WPth=0.3040;
    else if (_campaign =="2016preVFP_UL")     WPth=0.2598;
    else if (_campaign =="2016postVFP_UL")    WPth=0.2489;
    else if (_campaign == "Run3Summer22")     WPth=0.3086;
    else if (_campaign == "Run3Summer22EE")   WPth=0.3196;
    else if (_campaign == "Run3Summer23")     WPth=0.2431;
    else if (_campaign == "Run3Summer23BPix") WPth=0.2435;
    else cout<<"ProduceRecoCollection.h : Provide correct campaign name!"<<endl;
    bool medium_pass = temp.btagscore > WPth;
    
    if(passcut && cleaned_from_leptons){
      Jet.push_back(temp);
      if(Jet_btagDeepFlavB[i] > WPth) MediumbJet.push_back(temp);
    }
    
  }

}
