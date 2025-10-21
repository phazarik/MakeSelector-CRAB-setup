#include <algorithm>

bool alphaNumCompare(const TString &a, const TString &b) {
  const char *ca = a.Data();
  const char *cb = b.Data();
  while (*ca && *cb) {
    if (isdigit(*ca) && isdigit(*cb)) {
      // extract numbers
      long na = strtol(ca, (char**)&ca, 10);
      long nb = strtol(cb, (char**)&cb, 10);
      if (na != nb) return na < nb;
    } else {
      if (*ca != *cb) return *ca < *cb;
      ca++;
      cb++;
    }
  }
  return strlen(ca) < strlen(cb);
}

void find_nevents(
		  TString dumpdir = "skimmed_2L_2017_UL_2025-10-20",
		  TString find="nEvtTotal"
		  //TString find="genEventSumW"
		  )
{
  TString path = gSystem->ConcatFileName("/eos/user/p/phazarik/SKIMDUMP", dumpdir);
  TSystemDirectory dir(path, path);
  TList* allsamples = dir.GetListOfFiles();
  if (!allsamples) {cerr << "\033[031mError: Cannot open directory "<<path<<"\033[0m"<<endl; return;}
  cout<<"Searching in "<<path<<endl;
  
  // collect sample names
  vector<TString> sampleNames;
  for (TObject* obj : *allsamples) {
    TString s = obj->GetName();
    if (s=="." || s=="..") continue;
    sampleNames.push_back(s);
  }

  cout<< "\n-------------------------------------------------" <<endl;
  cout<<"\033[033m";
  cout<< setw(12) << left << "sample";
  cout<< setw(20) << left << "subsample";
  cout<< setw(12) << right << find <<endl;
  cout<<"\033[0m";
  cout<< "-------------------------------------------------" <<endl;

  vector<TString> invalidFiles;

  // loop over sorted sampleNames instead of allsamples
  sort(sampleNames.begin(), sampleNames.end(), alphaNumCompare);
  for (auto &sample : sampleNames) {

    //if(!sample.Contains("QCD")) continue;

    TString path2 = path + "/" + sample;
    TSystemDirectory subdir(path2, path2);
    TList* allsubsamples = subdir.GetListOfFiles();
    if (!allsubsamples) continue;

    // collect and sort subsamples
    vector<TString> subsampleNames;
    for (TObject* subobj : *allsubsamples) {
      TString subsample = subobj->GetName();
      if (subsample=="." || subsample=="..") continue;
      subsampleNames.push_back(subsample);
    }

    sort(subsampleNames.begin(), subsampleNames.end(), alphaNumCompare);
    for (auto &subsample : subsampleNames) {

      TString path3 = path2 + "/" + subsample;
      TSystemDirectory filedir(path3, path3);
      TList* files = filedir.GetListOfFiles();
      if (!files) continue;

      double count = 0;
      for (TObject* f : *files) {
        TString filename = f->GetName();
        if (!filename.EndsWith(".root")) continue;

        TString filepath = path3 + "/" + filename;
        TFile* file = TFile::Open(filepath);
        if (!file || file->IsZombie()) {
          cerr << "\033[031mError: Cannot open file " << filepath <<"\033[0m"<<endl;
          invalidFiles.push_back(filepath);
          continue;
        }

	TString histname = "hCount";
	if(find=="genEventSumW") histname = "hWt";
        TH1D* hist = dynamic_cast<TH1D*>(file->Get(histname));
        if (hist) {
          double bin = (find=="nEvtTotal" || find=="genEventSumW") ? 1 : 5;
          count += hist->GetBinContent((int)bin);
        } else {
          cerr << "\033[031mError: Histogram 'hCount' not found in " << filepath<<"\033[0m"<<endl;
        }
        file->Close();
      }

      cout<< setw(12) << left << sample;
      cout<< setw(20) << left << subsample;
      cout<< setw(12) << right << fixed << setprecision(0) << count <<endl;
    }
  }

  cout<< "-----------------------------------------" <<endl;
  cout<<"\nDone!"<<endl;
  if((int)invalidFiles.size()>0){
    cout<<"Invalid files found:"<<endl;
    for(int i=0; i<(int)invalidFiles.size(); i++) cout<<invalidFiles[i]<<endl;
  }
  cout<<endl;
}
