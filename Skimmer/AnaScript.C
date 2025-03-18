#define AnaScript_cxx
#include "AnaScript.h"
#include <TH2.h>
#include <TStyle.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <set>
#include "../includeHeaders.h"

void AnaScript::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}

void AnaScript::SlaveBegin(TTree *tree)
{
  TString option = GetOption();
  time(&start);

  //Set Year from campaign:
  if     (_campaign == "2018_UL") _year = 2018;
  else if(_campaign == "2017_UL") _year = 2017;
  else if((_campaign == "2016preVFP_UL") || (_campaign == "2016postVFP_UL"))   _year = 2016;
  else if((_campaign == "Run3Summer22")  || (_campaign == "Run3Summer22EE"))   _year = 2022;
  else if((_campaign == "Run3Summer23")  || (_campaign == "Run3Summer23BPix")) _year = 2023;
  else cout<<"main: Provide correct campaign name"<<endl;

  cout<<"\nParemeters:"<<endl;
  cout<<"Campaign = "<<_campaign<<endl;
  cout<<"Year   = "<<_year<<endl;
  cout<<"Sample = "<<_samplename<<endl;
  cout<<"Flag   = "<<_flag<<endl;
  cout<<"Data   = "<<_data<<"\n"<<endl;
  
  //Initializing counters:
  nEvtTotal=0; nEvtRan=0;  nEvtTrigger=0;
  nEvtPass=0;  nEvtBad=0;  nThrown=0;
  genEventsumw=0;
  
  //For skimmer
  tree->SetBranchStatus("*",0);
  ActivateBranch(tree);

  cout<<"n-events time(sec)"<<endl;
}

void AnaScript::SlaveTerminate()
{
  //Storing event information in a histogram:
  TH1D *hCount = new TH1D("hCount", "hCount;;",5, 0.5, 5.5);
  hCount->SetBinContent(1,genEventsumw);
  hCount->SetBinContent(2,nEvtTotal);
  hCount->SetBinContent(3,nEvtRan);
  hCount->SetBinContent(4,nEvtTrigger);
  hCount->SetBinContent(5,nEvtPass);
  hCount->GetXaxis()->SetBinLabel(1,"genEventSumW");
  hCount->GetXaxis()->SetBinLabel(2,"nEvtGen");
  hCount->GetXaxis()->SetBinLabel(3,"nEvtRan");
  hCount->GetXaxis()->SetBinLabel(4,"nEvtTrigger");
  hCount->GetXaxis()->SetBinLabel(5,"nEvtPass");

  //Write information in the output file:
  //_SkimFile->cd();
  hCount->Write();    cout<<"Event histogram written to file."<<endl;
  skimTree->Write();  cout<<"Skimmed tree written to file."<<endl;
  _SkimFile->Close(); cout<<"File written to disk."<<endl;

  //Display output:
  float goodevtfrac = ((float)nEvtRan)/((float)nEvtTotal);
  float trigevtfrac = ((float)nEvtTrigger)/((float)nEvtTotal);
  float passevtfrac = ((float)nEvtPass)/((float)nEvtTotal);
  float badevtfrac  = ((float)nEvtBad)/((float)nEvtTotal);//for VLLD
  float notgoldenevtfrac  = ((float)nThrown)/((float)nEvtTotal); //for data
  cout<<"---------------------------------------------"<<endl;
  cout<<"Summary:"<<endl;
  cout<<"nEvtTotal = "<<nEvtTotal<<endl;
  cout<<"nEvtRan = "<<nEvtRan<<" ("<<goodevtfrac*100<<" %)"<<endl;
  cout<<"nEvtTrigger = "<<nEvtTrigger<<" ("<<trigevtfrac*100<<" %)"<<endl;
  cout<<"nEvtPass = "<<nEvtPass<<" ("<<passevtfrac*100<<" %)"<<endl;
  cout<<"nEvtBad = "<<nEvtBad<<" ("<<badevtfrac*100<<" %)"<<endl;
  if(_data==0) cout<<"genEventsumw = "<<(int)genEventsumw<<endl;
  if(_data!=0) cout<<"nEvents not in golden json = "<<nThrown<<" ("<<notgoldenevtfrac*100<<" %)"<<endl;
  cout<<"---------------------------------------------"<<endl;
  
  time(&end);
  double time_taken = double(end - start);
  cout << setw(10) << left << "Time taken: " << (int)time_taken << " sec." << endl;
}

void AnaScript::Terminate()
{
  
}

//---------------------------------------------------------------------------------------------------------------
// EVENT LOOP
//---------------------------------------------------------------------------------------------------------------
Bool_t AnaScript::Process(Long64_t entry)
{
  //Branch management:
  fReader_2022.SetLocalEntry(entry);
  if (_data == 0) fReader_2022MC.SetLocalEntry(entry); 
  ReadBranch(); //for skimmer

  nEvtTotal++;
  if(_data==0) genEventsumw += (float)*Generator_weight;
  
  //Buffer display:
  time(&buffer);
  double time_buff = double(buffer-start);
  if (nEvtTotal % 100000 == 0) cout << setw(10) << left << nEvtTotal << " " << time_buff << endl;

  //Using flags:
  bool common  = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter &&
    *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter;
  bool eeBadSc = _data ? *Flag_eeBadScFilter : 1;

  GoodEvt2018 = (_year == 2018 ? common && eeBadSc && *Flag_BadPFMuonDzFilter && *Flag_ecalBadCalibFilter : 1);
  GoodEvt2017 = (_year == 2017 ? common && eeBadSc && *Flag_BadPFMuonDzFilter : 1);
  GoodEvt2016 = (_year == 2016 ? common && eeBadSc : 1);
  GoodEvt2022 = (_year == 2022 ? common && eeBadSc : 1);
  GoodEvt2023 = (_year == 2022 ? common && eeBadSc : 1);
  GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016 && GoodEvt2022 && GoodEvt2023;

  if(true){  
    nEvtRan++;

    //Triggers:
    triggerRes         = true; //default, always true for MC
    muon_trigger       = *HLT_SingleMuon;
    electron_trigger   = *HLT_SingleEle;
    overlapping_events = muon_trigger && electron_trigger;

    if(_data == 1){
      if(_flag != "egamma") triggerRes = muon_trigger;
      if(_flag == "egamma") triggerRes = electron_trigger && !muon_trigger;
    
      //Throw awaying bad data that are not included in the GoldenJson.
    }
      
    if(triggerRes){
      nEvtTrigger++;

      //Analysis begins here.
      //----------------------------------------------------------------------------------------------------------
      // OBJECT DEFINITIONS
      //----------------------------------------------------------------------------------------------------------
      
      //Gen particle block:
      genMuon.clear();  genElectron.clear();  genLightLepton.clear();
      genJet.clear();   vllep.clear();        vlnu.clear();
      bad_event = false;
      if(_data==0){
	createGenLightLeptons();
	createGenJets();
        SortGenObjects();
	SortPt(genMuon);
	SortPt(genElectron);
	SortPt(genLightLepton);
	//createSignalArrays();
	//SortVLL();
      }
      if(bad_event) nEvtBad++;

      //Reco-particle block:
      metpt = *PuppiMET_pt;
      metphi = *PuppiMET_phi;

      Muon.clear();    Electron.clear(); LightLepton.clear();
      Photon.clear();  Tau.clear();      Jet.clear();
      bJet.clear();    MediumbJet.clear();
      LooseLepton.clear(); LooseElectron.clear(); LooseMuon.clear();

      createLightLeptons();
      //createTaus();
      createJets();

      SortRecoObjects();

      //----------------------------------------------------------------------------------------------------------
      // Skimming
      //----------------------------------------------------------------------------------------------------------
      float ptcut_mu  = 26;
      float ptcut_ele = 35; 
      if(_year==2016) {ptcut_ele = 30; ptcut_mu = 26;}
      if(_year==2017) {ptcut_ele = 37; ptcut_mu = 29;}

      bool keep_this_event = false;
      
      if((int)LightLepton.size()==2){
	bool samesign = LightLepton.at(0).charge == LightLepton.at(1).charge;
	bool trigger = false;
	for(int i=0; i<(int)LightLepton.size(); i++){
	  int lepton_id = fabs(LightLepton.at(i).id);
	  float lepton_pt = LightLepton.at(i).v.Pt();
	  if(lepton_id == 11 && lepton_pt > ptcut_ele) trigger = true;
	  if(lepton_id == 13 && lepton_pt > ptcut_mu)  trigger = true;
	}
	bool reject_low_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 15;
	if(trigger && reject_low_resonances && samesign) keep_this_event = true;
      }
      if(bad_event) keep_this_event = false;

      //-------------------
      
      if(keep_this_event){
	nEvtPass++;
	skimTree->Fill();
      }
      //------------------
      
    }
    
  }
  
  return kTRUE;
}
