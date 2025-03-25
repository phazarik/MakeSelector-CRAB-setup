//----------------------------
// For local testing purposes
//----------------------------

//Run it in bash using the following:
// root -q -b -l 'test.C("../Skimmer/test_inputs/DYto2L-4Jets_MLL-50.root", "../Skimmer/test_outputs/test_driver.root", "Run3Summer22", "DYto2L-4Jets_MLL-50", "dy")'

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <filesystem>
#include <time.h>
using namespace std;

void test(
	  TString infile  = "/eos/user/p/phazarik/skimmed_2LSS_Run3Summer22/DYto2L/50toInf/*",
	  TString outfile = "test_outputs/skim_test.root",
	  TString campaign = "Run3Summer22",
	  TString sample = "DY",
	  TString flag = "dy"
	  )
{  
  TString arguments = "\""+infile+"\",\""+outfile+"\",\""+campaign+"\",\""+sample+"\",\""+flag+"\"";
  TString processline = ".x run_locally.C(" + arguments + ")";
  gSystem->Load("AnaScript_C.so");
  gROOT->ProcessLine(processline);
}
