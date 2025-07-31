//This function has different object selections.
//Reference: CMS AN-2025/131 (NPS-25-011)
//Contact person: Kumar Yash

int AnaScript::electronCustomID(Int_t bitmap,int quality, int skipCut){
  int qualityPass=1;
  for(int j=0;j<10;j++){
    if(j==skipCut) continue;
    if(((bitmap>>j*3) & 0x7)<quality){
      qualityPass=0;
      break;
    }
  }
  return qualityPass;
}

bool AnaScript::Veto3L4L(){

  //---------------------
  // OBJECT SELECTIONS
  //---------------------
  //The 3L/4L channels are defined using the following lepton collections.
  yash_llep.clear(); //for 3L/4Levent selections.
  yash_looseMuon.clear(); //for cleaning electron array.

  //Muons:
  unsigned int iterator_mu = (unsigned int)*nMuon;
  for(unsigned int i=0; i<iterator_mu; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(Muon_pt[i],Muon_eta[i],Muon_phi[i],0.105);
    temp.id = -13*Muon_charge[i];
    temp.ind = i;
    temp.charge = Muon_charge[i];
    temp.sip3d = Muon_sip3d[i];
    temp.reliso03 = Muon_pfRelIso03_all[i];
    temp.reliso04 = Muon_pfRelIso04_all[i];
    bool ptetacut = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4;
    if(_year == 2016) ptetacut = ptetacut && temp.sip3d < 12.0 && Jet_btagDeepFlavB[Muon_jetIdx[i]] < 0.6;      
    if(_year == 2017) ptetacut = ptetacut && temp.sip3d < 12.0 && Jet_btagDeepFlavB[Muon_jetIdx[i]] < 0.4;
    if(_year == 2018) ptetacut = ptetacut && temp.sip3d < 9.0  && Jet_btagDeepFlavB[Muon_jetIdx[i]] < 0.3;
    if(_year == 2022) ptetacut = ptetacut && temp.sip3d < 9.0  && Jet_btagDeepFlavB[Muon_jetIdx[i]] < 0.3;
    if(_year == 2023) ptetacut = ptetacut && temp.sip3d < 9.0  && Jet_btagDeepFlavB[Muon_jetIdx[i]] < 0.3;
    bool promptmuon = fabs(Muon_dxy[i])<0.05 && fabs(Muon_dz[i])<0.1;
    bool passcut_mediummuon = ptetacut && promptmuon && Muon_mediumId[i] && Muon_pfRelIso04_all[i]<0.15;
    bool passcut_loosemuon  = ptetacut && promptmuon && Muon_looseId[i]  && Muon_pfRelIso04_all[i]<1.0;
    if(passcut_loosemuon)  yash_looseMuon.push_back(temp);   //For cleaning the electron array.
    if(passcut_mediummuon) yash_llep.push_back(temp); //For event selections.
  }
  //Electrons:
  unsigned int iterator_ele = (unsigned int)*nElectron;
  for(unsigned int i=0; i<iterator_ele; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(Electron_pt[i],Electron_eta[i],Electron_phi[i],0.000511); 
    temp.id = -11*Electron_charge[i];
    temp.ind = i;
    temp.sip3d = Electron_sip3d[i];
    temp.charge = Electron_charge[i];
    temp.reliso03 = Electron_pfRelIso03_all[i];       
    bool ptetacut = temp.v.Pt()>10 && fabs(temp.v.Eta())<2.4;
    bool cleaned_from_muons = clean_from_array(temp, yash_looseMuon, 0.05);
    if(_year == 2016) ptetacut = ptetacut && temp.sip3d < 12.0 && Jet_btagDeepFlavB[Electron_jetIdx[i]] < 0.6;
    if(_year == 2017) ptetacut = ptetacut && temp.sip3d < 12.0 && Jet_btagDeepFlavB[Electron_jetIdx[i]] < 0.4;
    if(_year == 2018) ptetacut = ptetacut && temp.sip3d < 9.0  && Jet_btagDeepFlavB[Electron_jetIdx[i]] < 0.3;
    if(_year == 2022) ptetacut = ptetacut && temp.sip3d < 9.0  && Jet_btagDeepFlavB[Electron_jetIdx[i]] < 0.3;
    if(_year == 2023) ptetacut = ptetacut && temp.sip3d < 9.0  && Jet_btagDeepFlavB[Electron_jetIdx[i]] < 0.3;
    bool isprompt = false;
    double cut_dxy = fabs(temp.v.Eta()) <= 1.479 ? 0.05 : 0.1;
    double cut_dz  = fabs(temp.v.Eta()) <= 1.479 ? 0.1  : 0.2;
    if(fabs(Electron_dxy[i]) < cut_dxy && fabs(Electron_dz[i]) < cut_dz) isprompt = true;  
    bool passcut_mediumele = ptetacut && isprompt && Electron_cutBased[i]>2 && cleaned_from_muons;
    if(passcut_mediumele) yash_llep.push_back(temp);
  }

  //Sorting the lepton collection before using.
  for(int i=0; i<(int)yash_llep.size()-1; i++){
    for(int j=i+1; j<(int)yash_llep.size(); j++){
      if(yash_llep[i].v.Pt() < yash_llep[j].v.Pt())
	swap(yash_llep.at(i), yash_llep.at(j));
    }
  }

  //---------------------
  // EVENT SELECTIONS
  //---------------------
  bool event_4L = false;
  bool event_3L = false;

  //4L-inclusive
  if((int)yash_llep.size() > 3){
    //Trigger condition
    bool is_4L_trigger_event = false;
    for(int i=0; i<(int)yash_llep.size(); i++){
      if(_year == 2018 || _year == 2022 || _year == 2023){
	if(fabs(yash_llep.at(i).id) == 11 && yash_llep.at(i).v.Pt() > 35) is_4L_trigger_event = true;
	if(fabs(yash_llep.at(i).id) == 13 && yash_llep.at(i).v.Pt() > 26) is_4L_trigger_event = true;
      }
      if(_year == 2017){
	if(fabs(yash_llep.at(i).id) == 11 && yash_llep.at(i).v.Pt() > 35) is_4L_trigger_event = true;
	if(fabs(yash_llep.at(i).id) == 13 && yash_llep.at(i).v.Pt() > 29) is_4L_trigger_event = true;
      }
      if(_year == 2016){
	if(fabs(yash_llep.at(i).id) == 11 && yash_llep.at(i).v.Pt() > 30) is_4L_trigger_event = true;
	if(fabs(yash_llep.at(i).id) == 13 && yash_llep.at(i).v.Pt() > 26) is_4L_trigger_event = true;
      }
    }
    //Selections on dilepton mass and dR after passing offline trigger
    if(is_4L_trigger_event){
      if((yash_llep.at(0).v+yash_llep.at(1).v).M() > 12){
	if((yash_llep.at(0).v+yash_llep.at(2).v).M() > 12){
	  if((yash_llep.at(0).v+yash_llep.at(3).v).M() > 12){
	    if((yash_llep.at(1).v+yash_llep.at(2).v).M() > 12){
	      if((yash_llep.at(1).v+yash_llep.at(3).v).M() > 12){
		if((yash_llep.at(2).v+yash_llep.at(3).v).M() > 12){
		  if(yash_llep.at(0).v.DeltaR(yash_llep.at(1).v) > 0.2){
		    if(yash_llep.at(0).v.DeltaR(yash_llep.at(2).v) > 0.2){
		      if(yash_llep.at(0).v.DeltaR(yash_llep.at(3).v) > 0.2){
			if(yash_llep.at(1).v.DeltaR(yash_llep.at(2).v) > 0.2){
			  if(yash_llep.at(1).v.DeltaR(yash_llep.at(3).v) > 0.2){
			    if(yash_llep.at(2).v.DeltaR(yash_llep.at(3).v) > 0.2){
			      event_4L = true;
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
      
  //Exactly 3L
  if((int)yash_llep.size() == 3){
    //Trigger condition
    bool is_3L_trigger_event = false;
    for(int i=0; i<(int)yash_llep.size(); i++){
      if(_year == 2018 || _year == 2022 || _year == 2023){
	if(fabs(yash_llep.at(i).id) == 11 && yash_llep.at(i).v.Pt() > 35) is_3L_trigger_event = true;
	if(fabs(yash_llep.at(i).id) == 13 && yash_llep.at(i).v.Pt() > 26) is_3L_trigger_event = true;
      }
      if(_year == 2017){
	if(fabs(yash_llep.at(i).id) == 11 && yash_llep.at(i).v.Pt() > 35) is_3L_trigger_event = true;
	if(fabs(yash_llep.at(i).id) == 13 && yash_llep.at(i).v.Pt() > 29) is_3L_trigger_event = true;
      }
      if(_year == 2016){
	if(fabs(yash_llep.at(i).id) == 11 && yash_llep.at(i).v.Pt() > 30) is_3L_trigger_event = true;
	if(fabs(yash_llep.at(i).id) == 13 && yash_llep.at(i).v.Pt() > 26) is_3L_trigger_event = true;
      }
    }
    //Selections on dilepton mass and dR after passing offline trigger
    if(is_3L_trigger_event){
      if((yash_llep.at(0).v+yash_llep.at(1).v).M() > 12){
	if((yash_llep.at(0).v+yash_llep.at(2).v).M() > 12){
	  if((yash_llep.at(1).v+yash_llep.at(2).v).M() > 12){
	    if(yash_llep.at(0).v.DeltaR(yash_llep.at(1).v) > 0.2){
	      if(yash_llep.at(0).v.DeltaR(yash_llep.at(2).v) > 0.2){
		if(yash_llep.at(1).v.DeltaR(yash_llep.at(2).v) > 0.2){
		  event_3L = true;
		}
	      }
	    }
	  }
	}
      }
    }
  }

  //Final veto:
  bool veto_this_event = event_4L || event_3L;
  if(veto_this_event) cout<<"Vetoing 3L/4L event: "<<nEvtTotal<<endl;
  return veto_this_event;
}

bool AnaScript::VetoHEM(vector<Particle> jet){

  // HEM = Hadronic calorimeter Endcaps Minus issue.
  // The endcaps of the hadron calorimeter failed to cover the phase space at -3 <η< -1.3 and -1.57 <Φ< -0.87 during the 2018 data taking period. Events with jets that fall in this region are vetoed.

  // References:
  // 1. tWiki: https://twiki.cern.ch/twiki/bin/view/Main/ReviewOfEXO-22-012
  // 2. https://indico.cern.ch/event/920157/contributions/3866209/attachments/2055030/3445708/HEM_issue_forMETXMeeting.pdf

  bool veto_this_event = false;
  for(int i=0; i<(int)jet.size(); i++){
    float pt  = jet.at(i).v.Pt();
    float eta = jet.at(i).v.Eta();
    float phi = jet.at(i).v.Phi();
    bool HEM_eta_region = -3.00 < eta && eta < -1.30;
    bool HEM_phi_region = -1.57 < phi && phi < -0.87;
    if(_year == 2018){
      if(pt > 30 && HEM_eta_region && HEM_phi_region){
	veto_this_event = true;
	break;
      }
    }
  }
  //if(veto_this_event) cout<<"Vetoing HEM event: "<<nEvtTotal<<endl;
  return veto_this_event;
}
