void AnaScript::SortPt(vector<Particle> &part){
  //Note: This function is problematic.
  //It fails at some instances (not all).
  //Don't use it until it gets fixed.
  for(int i=0; i<(int)part.size()-1; i++){//first one
    for(int j=i+1; j<(int)part.size(); j++){//second one
      if( part[i].v.Pt() < part[j].v.Pt() ) swap(part.at(i), part.at(j));
    }
  }
}

void AnaScript::SortRecoObjects(){
  //Muons:
  for(int i=0; i<(int)Muon.size()-1; i++){
    for(int j=i+1; j<(int)Muon.size(); j++){
      if(Muon[i].v.Pt() < Muon[j].v.Pt() ) swap(Muon.at(i), Muon.at(j));}}  
  //Electrons:
  for(int i=0; i<(int)Electron.size()-1; i++){
    for(int j=i+1; j<(int)Electron.size(); j++){
      if(Electron[i].v.Pt() < Electron[j].v.Pt() ) swap(Electron.at(i), Electron.at(j));}}
  //LightLeptons
  for(int i=0; i<(int)LightLepton.size()-1; i++){
    for(int j=i+1; j<(int)LightLepton.size(); j++){
      if(LightLepton[i].v.Pt() < LightLepton[j].v.Pt() ) swap(LightLepton.at(i), LightLepton.at(j));}}
  //Photons:
  for(int i=0; i<(int)Photon.size()-1; i++){
    for(int j=i+1; j<(int)Photon.size(); j++){
      if(Photon[i].v.Pt() < Photon[j].v.Pt() ) swap(Photon.at(i), Photon.at(j));}}
  //Jets:
  for(int i=0; i<(int)Jet.size()-1; i++){
    for(int j=i+1; j<(int)Jet.size(); j++){
      if(Jet[i].v.Pt() < Jet[j].v.Pt() ) swap(Jet.at(i), Jet.at(j));}}
  //bJets:
  for(int i=0; i<(int)bJet.size()-1; i++){
    for(int j=i+1; j<(int)bJet.size(); j++){
      if(bJet[i].v.Pt() < bJet[j].v.Pt() ) swap(bJet.at(i), bJet.at(j));}}
  //MediumbJets:
  for(int i=0; i<(int)MediumbJet.size()-1; i++){
    for(int j=i+1; j<(int)MediumbJet.size(); j++){
      if(MediumbJet[i].v.Pt() < MediumbJet[j].v.Pt() ) swap(MediumbJet.at(i), MediumbJet.at(j));}}
  //LooseLeptons:
  for(int i=0; i<(int)LooseLepton.size()-1; i++){
    for(int j=i+1; j<(int)LooseLepton.size(); j++){
      if(LooseLepton[i].v.Pt() < LooseLepton[j].v.Pt() ) swap(LooseLepton.at(i), LooseLepton.at(j));}}
}

void AnaScript::SortGenObjects(){
  //genMuons:
  for(int i=0; i<(int)genMuon.size()-1; i++){
    for(int j=i+1; j<(int)genMuon.size(); j++){
      if(genMuon[i].v.Pt() < genMuon[j].v.Pt() ) swap(genMuon.at(i), genMuon.at(j));}}
  //genElectrons:
  for(int i=0; i<(int)genElectron.size()-1; i++){
    for(int j=i+1; j<(int)genElectron.size(); j++){
      if(genElectron[i].v.Pt() < genElectron[j].v.Pt() ) swap(genElectron.at(i), genElectron.at(j));}}
  //genLightLeptons:
  for(int i=0; i<(int)genLightLepton.size()-1; i++){
    for(int j=i+1; j<(int)genLightLepton.size(); j++){
      if(genLightLepton[i].v.Pt() < genLightLepton[j].v.Pt() ) swap(genLightLepton.at(i), genLightLepton.at(j));}}
  for(int i=0; i<(int)genJet.size()-1; i++){
    for(int j=i+1; j<(int)genJet.size(); j++){
      if(genJet[i].v.Pt() < genJet[j].v.Pt() ) swap(genJet.at(i), genJet.at(j));}}
}

void AnaScript::SortVLL(){
  //vllep:
  for(int i=0; i<(int)vllep.size()-1; i++){
    for(int j=i+1; j<(int)vllep.size(); j++){
      if(vllep[i].v.Pt() < vllep[j].v.Pt() ) swap(vllep.at(i), vllep.at(j));}}
  //vlnu:
  for(int i=0; i<(int)vlnu.size()-1; i++){
    for(int j=i+1; j<(int)vlnu.size(); j++){
      if(vlnu[i].v.Pt() < vlnu[j].v.Pt() ) swap(vlnu.at(i), vlnu.at(j));}}
}

float AnaScript::delta_phi(float phi1, float phi2){
  phi1 = TVector2::Phi_0_2pi(phi1);
  phi2 = TVector2::Phi_0_2pi(phi2);
  float dphi = fabs(phi1 - phi2);
  if(dphi>TMath::Pi()) dphi = 2*TMath::Pi() - dphi;
  return dphi;
}

int AnaScript::MotherID(int partindex, int momindex){
  int parid =GenPart_pdgId[partindex];
  int momid = GenPart_pdgId[momindex];
  while(parid==momid){
    partindex=momindex;
    momindex=GenPart_genPartIdxMother[momindex];
    parid =GenPart_pdgId[partindex];
    momid = GenPart_pdgId[momindex];
  }
  return momid;
}

float AnaScript::transv_mass(float lepE, float lepphi, float met, float metphi){
  float dphi = fabs(lepphi - metphi);
  if(dphi>TMath::Pi()) dphi = 2*TMath::Pi() - dphi;
  float mT = sqrt(2* lepE * met *(1-cos(dphi)));
  return mT;
}

//Cleaning funtions:
bool AnaScript::clean_from_array(Particle target, vector<Particle> array, float dRcut){
  bool result = true; //cleaned
  float dRmin = 1000;
  for(int i=0; i<(int)array.size(); i++){
    float dR = target.v.DeltaR(array.at(i).v);
    if(dR < dRmin) dRmin = dR;
  }
  //If the minimum dR of any Particle from the array with the target Particle is less than the dRcut,
  //then the target is not isolated.
  if(dRmin < dRcut) result = false;
  return result;
}

bool AnaScript::isMatchingWithGen(Particle reco, vector<Particle> gencollection){

  //Let's initialize minimun dR with some large value.
  float dR_min = 1000;
  
  //Looping over the gen-collection to minimize dR min
  for(int i=0; i<(int)gencollection.size(); i++){
    Particle gen = gencollection.at(i);
    //Compare reco and gen only if their IDs match. (flavor and charge)
    if(fabs(reco.id) == fabs(gen.id)){
      float dR = reco.v.DeltaR(gen.v);
      if(dR < dR_min) dR_min = dR;
    }
  }

  if(dR_min < 0.4) return true;
  else return false;
}
