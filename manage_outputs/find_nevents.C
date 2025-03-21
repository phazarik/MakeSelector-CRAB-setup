#include <iostream>
#include <iomanip>
#include <vector>
#include <TString.h>
#include <TFile.h>
#include <TKey.h> //accessing objects stored TFile
#include <TH1D.h>
#include <TSystem.h> //file and directory handling
#include <TSystemDirectory.h> //managing and listing directories
#include <TList.h>
#include <TSystemFile.h>//representing files in a ROOT directory listing
using namespace std;

void find_nevents(TString dumpdir = "skimmed_2LSS_Run3Summer22") {

  TString path = gSystem->ConcatFileName("/eos/user/p/phazarik/", dumpdir);
  
  TSystemDirectory dir(path, path);
  TList* allsamples = dir.GetListOfFiles();
  if (!allsamples) {std::cerr << "\033[031mError: Cannot open directory "<<path<<"\033[0m"<<endl; return;}

  cout<< "\n-----------------------------------------" <<endl;
  cout<<"\033[033m";
  cout<< setw(8) << left << "sample";
  cout<< setw(20) << left << "subsample";
  cout<< setw(12) << right << "nEvtTotal" <<endl;
  cout<<"\033[0m";
  cout<< "-----------------------------------------" <<endl;
  
  //Looping over objects kept in path:
  for (TObject* obj : *allsamples) {
    TString sample = obj->GetName();
    if (sample == "." || sample == "..") continue;
    TString path2 = path + "/" + sample;

    TSystemDirectory subdir(path2, path2);
    TList* allsubsamples = subdir.GetListOfFiles();
    if (!allsubsamples) continue;

    //Looping over objects kept in path+sample:
    for (TObject* subobj : *allsubsamples) {
      TString subsample = subobj->GetName();
      if (subsample == "." || subsample == "..") continue;
      
      TString path3 = path2 + "/" + subsample;
      
      TSystemDirectory filedir(path3, path3);
      TList* files = filedir.GetListOfFiles();
      if (!files) continue;

      // Initialize the total events counter for this subsample:
      double nEvtTotal = 0;

      int count = 0;
      //Looping over objects kept in path+sample+subsample:
      for (TObject* f : *files) {
	TString filename = f->GetName();
	if (!filename.EndsWith(".root")) continue;

	//Access each file:
	TString filepath = path3 + "/" + filename;
	TFile* file = TFile::Open(filepath);
	if (!file || file->IsZombie()) {cerr << "\033[031mError: Cannot open file " << filepath <<"\033[0m"<<endl; continue;}

	//Access histogram:
	TH1D* hist = dynamic_cast<TH1D*>(file->Get("hCount"));
	if (hist){
	  count += 1;
	  double nevt = hist->GetBinContent(2); 
	  //cout<<"Event in file #"<<count<<" = "<< fixed << setprecision(0) << nevt <<endl;
	  nEvtTotal += nevt;
	}
	else cerr << "\033[031mError: Histogram 'hCount' not found in " << filepath<<"\033[0m"<<endl;
	file->Close();
	//break; //file
      }

      cout<< setw(8)  << left  << sample;
      cout<< setw(20) << left  << subsample;
      cout<< setw(12) << right << fixed << setprecision(0) << nEvtTotal <<endl;
      
      break; //subsample
    }
    break; //sample
  }

  cout<< "-----------------------------------------" <<endl;
  cout<<"\nDone!\n"<<endl;
}
