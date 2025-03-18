//########################
// Gen Light Leptons:
//########################

void AnaScript::createGenLightLeptons(){

  int grandmomid=-1;
 
  //unsigned int iterator = (unsigned int)*(readerConfig->nGenPart);
  unsigned int iterator = (unsigned int)*nGenPart;
  for(unsigned int i=0; i<iterator; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]);
    temp.status = GenPart_status[i];
    temp.ind = i;
    temp.pdgid = GenPart_pdgId[i];
    temp.momid= MotherID(i,GenPart_genPartIdxMother[i]);

    int lepcharge=0;
    if(GenPart_pdgId[i]>0) lepcharge = -1; else lepcharge = 1;
    temp.charge = lepcharge;

    //General flags:
    bool promptdecay= abs(temp.momid)==15 ||abs(temp.momid)==23||abs(temp.momid)==24||abs(temp.momid)==25||(abs(temp.momid)>0 && abs(temp.momid)<7);
    //Setting very specific decay modes:
    bool WZbosondecay=false;
    bool ttzdecay=false;
    if(promptdecay){
      if(abs(temp.momid)==24 || abs(temp.momid)==23|| abs(temp.momid)==15){
	ttzdecay=true;
	int grandmomid=MotherID(GenPart_genPartIdxMother[i],GenPart_genPartIdxMother[GenPart_genPartIdxMother[i]]);
	//cout<<"GrandMom ID="<<grandmomid<<endl;
	if((abs(grandmomid)>0 && abs(grandmomid)<7))
	  WZbosondecay=true;    //Interested in very specific decay: W->l nu, Z->ll, mother is W or Z and grandmother should be a quark
      }
    }
    
    //##############
    //genMuon block:
    //##############
    bool passcutmu= abs(temp.pdgid)==13 && temp.status==1 && temp.v.Pt()>5 && fabs(temp.v.Eta())<2.4;
    bool motherisnotmu= abs(temp.momid)!=13 && GenPart_pdgId[GenPart_genPartIdxMother[i]]!=22;
    passcutmu = passcutmu && motherisnotmu && promptdecay; 
    if(passcutmu){     	
      genMuon.push_back(temp);
      genLightLepton.push_back(temp);
    }

    //##################
    //genElectron block:
    //##################
    bool passcutele= abs(temp.pdgid)==11 && temp.status==1 && temp.v.Pt()>5 && fabs(temp.v.Eta())<2.4;
    bool motherisnotele= abs(temp.momid)!=11 && GenPart_pdgId[GenPart_genPartIdxMother[i]]!=22;
    passcutele = passcutele && motherisnotele && promptdecay; 
    if(passcutele){
      genElectron.push_back(temp);
      genLightLepton.push_back(temp);
    }
     
  }// for genpart

}

void AnaScript::createGenJets(){
  //unsigned int iterator = (unsigned int)*(readerConfig->nGenJet);
  unsigned int iterator = (unsigned int)*nGenJet;
  for(unsigned int i=0; i<iterator; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(GenJet_pt[i],GenJet_eta[i],GenJet_phi[i],GenJet_mass[i]);
    temp.ind = i;

    bool passcuts = temp.v.Pt()>30 && fabs(temp.v.Eta())<2.4;
    if(passcuts) genJet.push_back(temp);
  }
}

//SIGNAL:
void AnaScript::createSignalArrays(){
  //Creating signal arrays and flagging the bad events:

  /*
  //Printing out the GenPart Array:
  int test_event = 100;
  if(nEvtTotal == test_event){
    cout<<"\n------------------Event display-------------------"<<endl;
    cout<<"index\tpdgId\tname\tmomind\tmomid\tname\tstat"<<endl;
    for(unsigned int i=0; i< (*nGenPart); i++){
      TString mom = "--";
      int momid = GenPart_genPartIdxMother[GenPart_pdgId[i]];
      if(fabs(momid)<10000) mom=(TString)to_string(momid);
      cout<<i<<"\t";
      cout<<GenPart_pdgId[i]<<"\t";
      cout<<ParticleName(GenPart_pdgId[i])<<"\t";
      cout<<GenPart_genPartIdxMother[i]<<"\t";
      cout<<mom<<"\t";
      cout<<ParticleName(momid)<<"\t";
      cout<<GenPart_status[i]<<endl;
    }
    cout<<"--------------------------------------------------\n"<<endl;
    }*/
  //unsigned int iterator = (unsigned int)*(readerConfig->nGenPart);
  unsigned int iterator = (unsigned int)*nGenPart;
  for(unsigned int i=0; i<iterator; i++){
    Particle temp;
    temp.v.SetPtEtaPhiM(GenPart_pt[i],GenPart_eta[i],GenPart_phi[i],GenPart_mass[i]);
    temp.status = GenPart_status[i];
    temp.ind = i;
    temp.pdgid = GenPart_pdgId[i];
    //temp.momid= MotherID(i,GenPart_genPartIdxMother[i]);
    temp.momid = GenPart_pdgId[GenPart_genPartIdxMother[i]]; //Not fixing the mother right now

    //h.sig[0]->Fill(GenPart_pdgId[i], 1.0);

    bool mother_is_Z = (temp.momid == 23);
    bool mother_is_W = (fabs(temp.momid) == 24);
    bool not_its_own_mother = (temp.momid != temp.pdgid); //To avoid overcounting

    //Finding daughters:
    vector<int> daughter_ind, daughter_id;
    daughter_ind.clear(); daughter_id.clear();

    //unsigned int iterator2 = (unsigned int)*(readerConfig->nGenPart);
    unsigned int iterator2 = (unsigned int)*nGenPart;
    for(unsigned int j=0; j<iterator2; j++){
      float id = GenPart_pdgId[j];
      //float momid = GenPart_pdgId[GenPart_genPartIdxMother[i]];
      float momid = MotherID(j,GenPart_genPartIdxMother[j]);
      //remove identical daughetrs:
      bool unique_daughter = true;
      if(momid == GenPart_pdgId[i]){ //If mother of the j-th particle is the i-th particle,
	for(int k=0; k<(int)daughter_id.size(); k++){
	  if(id == daughter_id.at(k)) unique_daughter = false;
	}
	if(unique_daughter){
	  daughter_ind.push_back(j); //Then the particle at j-th index is a daughter.
	  daughter_id.push_back(id);
	}
      }
    }
    temp.dauind = daughter_ind;
    temp.dauid = daughter_id;

    //Setting decaymodes:
    //If the particle decays into W, Z or H, decaymode = 1, 2 or 3 respectively.
    temp.decaymode = 0;
    for(int j=0; j<(int)temp.dauid.size(); j++){
      if(fabs(temp.dauid[j]) == 23)      temp.decaymode = 2; //Z
      else if(fabs(temp.dauid[j]) == 24) temp.decaymode = 1; //W
      else if(fabs(temp.dauid[j]) == 25) temp.decaymode = 3; //H
    }   
    
    if(fabs(temp.pdgid) == 17 && not_its_own_mother){
      if(temp.pdgid == 17) temp.charge = -1;
      else if(temp.pdgid == -17) temp.charge = +1;
      vllep.push_back(temp);
    }

    else if(fabs(temp.pdgid) == 18 && not_its_own_mother){
      if(temp.pdgid == 18) temp.charge = -1;
      else if(temp.pdgid == -18) temp.charge = +1;
      //temp.charge = 0;
      vlnu.push_back(temp);
    }
  }
  
}
