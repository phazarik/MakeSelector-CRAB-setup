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
#include "SkimmerHelper.h"

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
  cout<<"Data   = "<<_data<<endl;
  
  //Initializing counters:
  nEvtGen=tree->GetEntries();
  nEvtTotal=0; nEvtRan=0;  nEvtTrigger=0;
  nEvtPass=0;  nEvtBad=0;  nThrown=0; nEvtVeto=0;
  genEventsumw=0;
  
  //For skimmer
  ActivateBranch(tree);

  cout << "\n"
     << right << setw(8) << "Progress"
     << right << setw(12) << "nEvents"
     << right << setw(8) << "Time" << endl;
}

void AnaScript::SlaveTerminate()
{
  //Storing event information in a histogram:
  TH1D *hCount = new TH1D("hCount", "hCount;;", 6, 0.5, 6.5);
  hCount->SetBinContent(1,nEvtTotal);
  hCount->SetBinContent(2,nEvtRan);
  hCount->SetBinContent(3,nEvtTrigger);
  hCount->SetBinContent(4,nEvtVeto);
  hCount->SetBinContent(5,nEvtPass);
  hCount->SetBinContent(6,nEvtBad);
  hCount->GetXaxis()->SetBinLabel(1,"nEvtGen");
  hCount->GetXaxis()->SetBinLabel(2,"nEvtRan");
  hCount->GetXaxis()->SetBinLabel(3,"nEvtTrigger");
  hCount->GetXaxis()->SetBinLabel(4,"nEvtVeto");
  hCount->GetXaxis()->SetBinLabel(5,"nEvtPass");
  hCount->GetXaxis()->SetBinLabel(6,"nEvtBad");

  TH1D *hWt = new TH1D("hWt", "hWt;;", 1, 0, 1);
  hWt->SetBinContent(1,genEventsumw);
  hWt->GetXaxis()->SetBinLabel(1,"genEventSumW");

  //Write information in the output file:
  //_SkimFile->cd();
  hCount->Write();    cout<<"Event counts written to file."<<endl;
  hWt->Write();       cout<<"Event weights written to file."<<endl;
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
  cout<<"nEvtVeto = "<<nEvtVeto<<endl;
  if(_data==0) cout<<"genEventsumw = "<<fixed<<setprecision(2)<<genEventsumw<<endl;
  if(_data!=0) cout<<"nEvents not in golden json = "<<nThrown<<" ("<<notgoldenevtfrac*100<<" %)"<<endl;
  cout<<"---------------------------------------------"<<endl;
  
  time(&end);
  double time_taken = double(end - start);
  cout<<"\n\033[34mTime taken to process = " << (int)time_taken << " seconds.\033[0m"<< endl;
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
  fReader.SetLocalEntry(entry);
  if (_data == 0){
    fReader_MC.SetLocalEntry(entry);
    if (_flag!="qcd") fReader_nonQCD.SetLocalEntry(entry);
  } 
  ReadBranch(); //for skimmer
  
  nEvtTotal++;
  if(_data==0) genEventsumw += (float)*Generator_weight;
  
  //Setting verbosity:
  if (nEvtTotal % 10000 == 0) {
    time(&buffer);
    double time_buff = double(buffer-start);
    double frac = (double)nEvtTotal / nEvtGen * 100.0;
    string progress = (ostringstream() << fixed << setprecision(2) << frac << "%").str();
    cout << right << setw(8) << progress
	 << right << setw(12) << nEvtTotal
	 << right << setw(8) << fixed << setprecision(0) << time_buff <<endl;
  }
  
  //Using flags:
  bool common  = *Flag_goodVertices && *Flag_globalSuperTightHalo2016Filter && *Flag_HBHENoiseFilter &&
    *Flag_HBHENoiseIsoFilter && *Flag_EcalDeadCellTriggerPrimitiveFilter && *Flag_BadPFMuonFilter;
  bool eeBadSc = _data ? *Flag_eeBadScFilter : 1;

  /*
  GoodEvt2018 = (_year == 2018 ? common && eeBadSc && *Flag_BadPFMuonDzFilter && *Flag_ecalBadCalibFilter : 1);
  GoodEvt2017 = (_year == 2017 ? common && eeBadSc && *Flag_BadPFMuonDzFilter : 1);
  GoodEvt2016 = (_year == 2016 ? common && eeBadSc : 1);
  GoodEvt2022 = (_year == 2022 ? common && eeBadSc : 1);
  GoodEvt2023 = (_year == 2022 ? common && eeBadSc : 1);
  GoodEvt = GoodEvt2018 && GoodEvt2017 && GoodEvt2016 && GoodEvt2022 && GoodEvt2023;*/
  GoodEvt=true;

  if(GoodEvt){  
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
	createSignalArrays();
	SortVLL();
      }
      if(bad_event) nEvtBad++;

      //Reco-particle block:
      metpt = *PuppiMET_pt;
      metphi = *PuppiMET_phi;

      Muon.clear();    Electron.clear();          LightLepton.clear();
      Photon.clear();  Tau.clear();               Jet.clear();
      bJet.clear();    MediumbJet.clear();        FatJet.clear();
      LooseLepton.clear(); LooseElectron.clear(); LooseMuon.clear();
      
      createLightLeptons();
      //createTaus();
      createJets();
      createFatJets();
      
      SortRecoObjects();

      //-------------------------------------------------------------------------------------------------------
      // Skimming
      //-------------------------------------------------------------------------------------------------------
      float ptcut_mu  = 26;
      float ptcut_ele = 35; 
      if(_year==2016) {ptcut_ele = 30; ptcut_mu = 26;}
      if(_year==2017) {ptcut_ele = 37; ptcut_mu = 29;}

      bool keep_this_event = false;

      //------------ baseline selections -------------
      bool evt_2LSS = false;
      bool evt_2LOS = false;
      
      if((int)LightLepton.size()==2){
	
	//Check offline trigger:
	bool trigger = false;
	for(int i=0; i<(int)LightLepton.size(); i++){
	  int lepton_id = fabs(LightLepton.at(i).id);
	  float lepton_pt = LightLepton.at(i).v.Pt();
	  if(lepton_id == 11 && lepton_pt > ptcut_ele) trigger = true;
	  if(lepton_id == 13 && lepton_pt > ptcut_mu)  trigger = true;
	}
	if(LooseLepton.size() > 2) trigger = false; //Veto additional loose leptons

	//Check resonance-cut:
	bool reject_low_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 15;
	bool reject_most_resonances = (LightLepton.at(0).v + LightLepton.at(1).v).M() > 150;

	//Check lepton charges:
	bool samesign = LightLepton.at(0).charge == LightLepton.at(1).charge;

	//Define events:
	if(trigger && reject_low_resonances && samesign)   evt_2LSS = true; //2LSS
	if(trigger && reject_most_resonances && !samesign) evt_2LOS = true; //2LOS
	if(evt_2LSS || evt_2LOS) keep_this_event = true; //keep both 2LSS and 2LOS
	
	//Veto additional events
	bool veto_3L4L_event = Veto3L4L();
	bool veto_HEM_event  = VetoHEM(Jet);
	bool veto_this_event = veto_3L4L_event || veto_HEM_event;
	if(veto_this_event){
	  nEvtVeto++;
	  keep_this_event = false;
	  evt_2LSS = false;
	  evt_2LOS = false;
	}	
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
