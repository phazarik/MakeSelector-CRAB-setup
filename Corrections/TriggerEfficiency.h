//-------------------------------------------------------------------------------------------
// SingleLepton trigger efficiency, as measured in August, 2025
// Method: https://github.com/phazarik/VLLSearch-Run3/tree/main/ExtraTools/triggerEfficiency
//-------------------------------------------------------------------------------------------

double AnaScript::GetLeptonTriggerEfficiency(Particle lepton, TString mode){
  double sf = 1.0; 
  int flav = fabs(lepton.id);  
  if(flav == 13)      sf = TrigEff_HLT_IsoMuXX(lepton, mode);
  else if(flav == 11) sf = TrigEff_HLT_EleXX_WPTight_Gsf(lepton, mode);
  else cout<<"Warning: Provide correct lepton while calculating trigger sf."<<endl;
  return sf;
}

//--------------------
// SingleMuon trigger
//---------------------
double AnaScript::TrigEff_HLT_IsoMuXX(Particle lepton, TString mode){

  double eff = 1.0;
  float pT  = lepton.v.Pt();
  float eta = fabs(lepton.v.Eta());
  if( pT<10 || eta>2.4 ) return 0.0;

  bool barrel = eta<=1.479;
  bool endcap = eta >1.479;
  
  if(_campaign == "2016preVFP_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.954653 * (1 + TMath::Erf((pT - 23.837283) / (2 * 0.669658)));
      else if(mode=="nom")      eff = 0.5 * 0.954040 * (1 + TMath::Erf((pT - 23.804548) / (2 * 0.681984)));
      else if(mode=="systdown") eff = 0.5 * 0.953427 * (1 + TMath::Erf((pT - 23.771813) / (2 * 0.694310)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.961241 * (1 + TMath::Erf((pT - 23.885174) / (2 * 0.852528)));
      else if(mode=="nom")      eff = 0.5 * 0.959888 * (1 + TMath::Erf((pT - 23.825226) / (2 * 0.881169)));
      else if(mode=="systdown") eff = 0.5 * 0.958534 * (1 + TMath::Erf((pT - 23.765279) / (2 * 0.909809)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "2016postVFP_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.963560 * (1 + TMath::Erf((pT - 23.969376) / (2 * 0.356460)));
      else if(mode=="nom")      eff = 0.5 * 0.962936 * (1 + TMath::Erf((pT - 23.952643) / (2 * 0.362815)));
      else if(mode=="systdown") eff = 0.5 * 0.962311 * (1 + TMath::Erf((pT - 23.935909) / (2 * 0.369170)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.962746 * (1 + TMath::Erf((pT - 24.009664) / (2 * 0.446861)));
      else if(mode=="nom")      eff = 0.5 * 0.961382 * (1 + TMath::Erf((pT - 23.971009) / (2 * 0.465321)));
      else if(mode=="systdown") eff = 0.5 * 0.960017 * (1 + TMath::Erf((pT - 23.932354) / (2 * 0.483782)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "2017_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.929310 * (1 + TMath::Erf((pT - 26.945585) / (2 * 0.597724)));
      else if(mode=="nom")      eff = 0.5 * 0.928835 * (1 + TMath::Erf((pT - 26.942436) / (2 * 0.599793)));
      else if(mode=="systdown") eff = 0.5 * 0.928360 * (1 + TMath::Erf((pT - 26.939287) / (2 * 0.601863)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.937179 * (1 + TMath::Erf((pT - 26.918278) / (2 * 0.780193)));
      else if(mode=="nom")      eff = 0.5 * 0.936175 * (1 + TMath::Erf((pT - 26.902735) / (2 * 0.790323)));
      else if(mode=="systdown") eff = 0.5 * 0.935171 * (1 + TMath::Erf((pT - 26.887193) / (2 * 0.800453)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "2018_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.947488 * (1 + TMath::Erf((pT - 23.951495) / (2 * 0.366571)));
      else if(mode=="nom")      eff = 0.5 * 0.947144 * (1 + TMath::Erf((pT - 23.942346) / (2 * 0.370153)));
      else if(mode=="systdown") eff = 0.5 * 0.946800 * (1 + TMath::Erf((pT - 23.933198) / (2 * 0.373735)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.955539 * (1 + TMath::Erf((pT - 23.972886) / (2 * 0.449100)));
      else if(mode=="nom")      eff = 0.5 * 0.954804 * (1 + TMath::Erf((pT - 23.951084) / (2 * 0.459585)));
      else if(mode=="systdown") eff = 0.5 * 0.954068 * (1 + TMath::Erf((pT - 23.929283) / (2 * 0.470070)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer22"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.953740 * (1 + TMath::Erf((pT - 23.846912) / (2 * 0.580634)));
      else if(mode=="nom")      eff = 0.5 * 0.952872 * (1 + TMath::Erf((pT - 23.757106) / (2 * 0.611859)));
      else if(mode=="systdown") eff = 0.5 * 0.952003 * (1 + TMath::Erf((pT - 23.667301) / (2 * 0.643085)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.931814 * (1 + TMath::Erf((pT - 23.941327) / (2 * 0.676495)));
      else if(mode=="nom")      eff = 0.5 * 0.930018 * (1 + TMath::Erf((pT - 23.804970) / (2 * 0.731551)));
      else if(mode=="systdown") eff = 0.5 * 0.928221 * (1 + TMath::Erf((pT - 23.668612) / (2 * 0.786608)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer22EE"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.948703 * (1 + TMath::Erf((pT - 24.309129) / (2 * 0.424750)));
      else if(mode=="nom")      eff = 0.5 * 0.948106 * (1 + TMath::Erf((pT - 24.238438) / (2 * 0.450435)));
      else if(mode=="systdown") eff = 0.5 * 0.947509 * (1 + TMath::Erf((pT - 24.167748) / (2 * 0.476119)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.940144 * (1 + TMath::Erf((pT - 24.352545) / (2 * 0.515589)));
      else if(mode=="nom")      eff = 0.5 * 0.938971 * (1 + TMath::Erf((pT - 24.274768) / (2 * 0.548969)));
      else if(mode=="systdown") eff = 0.5 * 0.937799 * (1 + TMath::Erf((pT - 24.196991) / (2 * 0.582350)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer23"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.949485 * (1 + TMath::Erf((pT - 24.876439) / (2 * 0.088150)));
      else if(mode=="nom")      eff = 0.5 * 0.948750 * (1 + TMath::Erf((pT - 24.063071) / (2 * 0.375222)));
      else if(mode=="systdown") eff = 0.5 * 0.948015 * (1 + TMath::Erf((pT - 23.249704) / (2 * 0.662293)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.956061 * (1 + TMath::Erf((pT - 24.394306) / (2 * 0.512138)));
      else if(mode=="nom")      eff = 0.5 * 0.954457 * (1 + TMath::Erf((pT - 24.297656) / (2 * 0.553183)));
      else if(mode=="systdown") eff = 0.5 * 0.952852 * (1 + TMath::Erf((pT - 24.201006) / (2 * 0.594228)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer23BPix"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.948752 * (1 + TMath::Erf((pT - 24.496356) / (2 * 0.363099)));
      else if(mode=="nom")      eff = 0.5 * 0.946835 * (1 + TMath::Erf((pT - 24.275500) / (2 * 0.439041)));
      else if(mode=="systdown") eff = 0.5 * 0.944919 * (1 + TMath::Erf((pT - 24.054643) / (2 * 0.514983)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.957771 * (1 + TMath::Erf((pT - 24.643990) / (2 * 0.346971)));
      else if(mode=="nom")      eff = 0.5 * 0.953730 * (1 + TMath::Erf((pT - 24.248174) / (2 * 0.507612)));
      else if(mode=="systdown") eff = 0.5 * 0.949689 * (1 + TMath::Erf((pT - 23.852359) / (2 * 0.668253)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else cout<<"\033[31mTrigEff: invalid campaign!\033[0m"<<endl;
  
  return eff;
}

//------------------------
// SingleElectron trigger
//------------------------
double AnaScript::TrigEff_HLT_EleXX_WPTight_Gsf(Particle lepton, TString mode){

  double eff = 1.0;
  float pT  = lepton.v.Pt();
  float eta = fabs(lepton.v.Eta());
  if( pT<10 || eta>2.4 ) return 0.0;

  bool barrel = eta<=1.479;
  bool endcap = eta >1.479;
  
  if(_campaign == "2016preVFP_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.981292 * (1 + TMath::Erf((pT - 26.708391) / (2 * 1.090365)));
      else if(mode=="nom")      eff = 0.5 * 0.980446 * (1 + TMath::Erf((pT - 26.698758) / (2 * 1.103185)));
      else if(mode=="systdown") eff = 0.5 * 0.979601 * (1 + TMath::Erf((pT - 26.689126) / (2 * 1.116006)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.988878 * (1 + TMath::Erf((pT - 27.616406) / (2 * 1.364634)));
      else if(mode=="nom")      eff = 0.5 * 0.986765 * (1 + TMath::Erf((pT - 27.574657) / (2 * 1.405632)));
      else if(mode=="systdown") eff = 0.5 * 0.984652 * (1 + TMath::Erf((pT - 27.532909) / (2 * 1.446630)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "2016postVFP_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.970315 * (1 + TMath::Erf((pT - 26.616418) / (2 * 0.010000)));
      else if(mode=="nom")      eff = 0.5 * 0.969239 * (1 + TMath::Erf((pT - 26.207685) / (2 * 0.332775)));
      else if(mode=="systdown") eff = 0.5 * 0.968164 * (1 + TMath::Erf((pT - 25.798951) / (2 * 0.987692)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.985168 * (1 + TMath::Erf((pT - 27.847962) / (2 * 1.466818)));
      else if(mode=="nom")      eff = 0.5 * 0.982294 * (1 + TMath::Erf((pT - 27.792238) / (2 * 1.519693)));
      else if(mode=="systdown") eff = 0.5 * 0.979420 * (1 + TMath::Erf((pT - 27.736514) / (2 * 1.572567)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "2017_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.948809 * (1 + TMath::Erf((pT - 33.019150) / (2 * 0.805303)));
      else if(mode=="nom")      eff = 0.5 * 0.948087 * (1 + TMath::Erf((pT - 33.014883) / (2 * 0.807963)));
      else if(mode=="systdown") eff = 0.5 * 0.947364 * (1 + TMath::Erf((pT - 33.010616) / (2 * 0.810624)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.958473 * (1 + TMath::Erf((pT - 34.020240) / (2 * 1.527333)));
      else if(mode=="nom")      eff = 0.5 * 0.956660 * (1 + TMath::Erf((pT - 34.001716) / (2 * 1.541503)));
      else if(mode=="systdown") eff = 0.5 * 0.954846 * (1 + TMath::Erf((pT - 33.983191) / (2 * 1.555672)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "2018_UL"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.955390 * (1 + TMath::Erf((pT - 33.094542) / (2 * 0.749700)));
      else if(mode=="nom")      eff = 0.5 * 0.954918 * (1 + TMath::Erf((pT - 33.091970) / (2 * 0.751299)));
      else if(mode=="systdown") eff = 0.5 * 0.954446 * (1 + TMath::Erf((pT - 33.089399) / (2 * 0.752897)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.974775 * (1 + TMath::Erf((pT - 33.019429) / (2 * 1.214851)));
      else if(mode=="nom")      eff = 0.5 * 0.973760 * (1 + TMath::Erf((pT - 33.009364) / (2 * 1.223297)));
      else if(mode=="systdown") eff = 0.5 * 0.972744 * (1 + TMath::Erf((pT - 32.999300) / (2 * 1.231742)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer22"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.932956 * (1 + TMath::Erf((pT - 30.331113) / (2 * 1.118045)));
      else if(mode=="nom")      eff = 0.5 * 0.931914 * (1 + TMath::Erf((pT - 30.311388) / (2 * 1.129589)));
      else if(mode=="systdown") eff = 0.5 * 0.930872 * (1 + TMath::Erf((pT - 30.291662) / (2 * 1.141133)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.957088 * (1 + TMath::Erf((pT - 29.236527) / (2 * 2.017859)));
      else if(mode=="nom")      eff = 0.5 * 0.952509 * (1 + TMath::Erf((pT - 29.161100) / (2 * 2.067861)));
      else if(mode=="systdown") eff = 0.5 * 0.947929 * (1 + TMath::Erf((pT - 29.085674) / (2 * 2.117863)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer22EE"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.965664 * (1 + TMath::Erf((pT - 33.319427) / (2 * 1.255990)));
      else if(mode=="nom")      eff = 0.5 * 0.962697 * (1 + TMath::Erf((pT - 33.297239) / (2 * 1.266952)));
      else if(mode=="systdown") eff = 0.5 * 0.959729 * (1 + TMath::Erf((pT - 33.275052) / (2 * 1.277915)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.971225 * (1 + TMath::Erf((pT - 32.986362) / (2 * 1.434580)));
      else if(mode=="nom")      eff = 0.5 * 0.965744 * (1 + TMath::Erf((pT - 32.929387) / (2 * 1.464766)));
      else if(mode=="systdown") eff = 0.5 * 0.960263 * (1 + TMath::Erf((pT - 32.872412) / (2 * 1.494951)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer23"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.958318 * (1 + TMath::Erf((pT - 35.053126) / (2 * 0.425648)));
      else if(mode=="nom")      eff = 0.5 * 0.956914 * (1 + TMath::Erf((pT - 34.948848) / (2 * 0.472523)));
      else if(mode=="systdown") eff = 0.5 * 0.955509 * (1 + TMath::Erf((pT - 34.844571) / (2 * 0.519399)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.969819 * (1 + TMath::Erf((pT - 35.234868) / (2 * 0.371504)));
      else if(mode=="nom")      eff = 0.5 * 0.966932 * (1 + TMath::Erf((pT - 34.985523) / (2 * 0.492576)));
      else if(mode=="systdown") eff = 0.5 * 0.964045 * (1 + TMath::Erf((pT - 34.736178) / (2 * 0.613648)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else if(_campaign == "Run3Summer23BPix"){
    if(barrel){
      if     (mode=="systup")   eff = 0.5 * 0.961535 * (1 + TMath::Erf((pT - 35.215387) / (2 * 0.370555)));
      else if(mode=="nom")      eff = 0.5 * 0.957858 * (1 + TMath::Erf((pT - 34.971512) / (2 * 0.485728)));
      else if(mode=="systdown") eff = 0.5 * 0.954181 * (1 + TMath::Erf((pT - 34.727638) / (2 * 0.600901)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
    else if(endcap){
      if     (mode=="systup")   eff = 0.5 * 0.976184 * (1 + TMath::Erf((pT - 32.811267) / (2 * 1.608164)));
      else if(mode=="nom")      eff = 0.5 * 0.968842 * (1 + TMath::Erf((pT - 32.720349) / (2 * 1.659981)));
      else if(mode=="systdown") eff = 0.5 * 0.961500 * (1 + TMath::Erf((pT - 32.629432) / (2 * 1.711799)));
      else cout<<"\033[31mTrigEff: invalid mode!\033[0m"<<endl;
    }
  }
  else cout<<"\033[31mTrigEff: invalid campaign!\033[0m"<<endl;
  
  return eff;
}
