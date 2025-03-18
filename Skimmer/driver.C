//-----------------------------------------------------
// Feeding parameters and running the compiled library.
//-----------------------------------------------------

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <filesystem>
using namespace std;

void driver(
	    TString infile  = "test_inputs/DYto2L-4Jets_MLL-50.root",
	    TString outfile = "test_outputs/test_driver.root",
	    TString campaign = "Run3Summer22",
	    TString sample = "DYJetsToLL_M50",
	    TString flag = "dy"
	    )
{
  filesystem::path currentDir = filesystem::current_path();
  TString pwd = TString(currentDir.c_str());
  cout<<"Working directory = "<<pwd<<endl;
  
  TString arguments = "\""+infile+"\",\""+outfile+"\",\""+campaign+"\",\""+sample+"\",\""+flag+"\"";
  TString processline = ".x "+pwd+"/run_locally.C(" + arguments + ")";

  gSystem->Load(pwd+"/AnaScript_C.so");
  gROOT->ProcessLine(processline);
}
