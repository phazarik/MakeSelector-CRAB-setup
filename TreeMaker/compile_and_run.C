//-----------------------------------------------------
// Feeding parameters and running the compiled library.
//-----------------------------------------------------

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <filesystem>
#include <time.h>
using namespace std;

void compile_and_run(
		     //TString infile  = "/eos/home-p/phazarik/GitHub/MakeSelector-CRAB-setup/Skimmer/test_inputs/2018_UL_DYJetsToLL_M-50.root",
		     TString infile = "/eos/home-p/phazarik/xrdcp_samples/RunIISummer20UL18NanoAODv9/VLLD_mu_M400_TuneCP5_13TeV-madgraph-pythia8/F54E0E1D-24AF-684D-9B5A-7FE4E37F018D.root",
		     TString outfile = "test_outputs/tree_testcompile.root",
		     TString campaign = "2018_UL",
		     TString sample = "vlld",
		     TString flag = "doublet"
		     )
{

  TString sourceCodeDir = gSystem->DirName(__FILE__);  // directory of this macro
  
  TString arguments = "\""+infile+"\",\""+outfile+"\",\""+campaign+"\",\""+sample+"\",\""+flag+"\"";
  TString processline = ".x "+sourceCodeDir+"/run.C(" + arguments + ")"; //testing purposes

  //Compiling and loading the source code:
  time_t compile_start, compile_end;
  cout<<"Compiling the source code ..."<<endl;
  time(&compile_start);
  gSystem->CompileMacro(sourceCodeDir+"/AnaScript.C", "k");
  time(&compile_end);
  cout<<"Compilation success!"<<endl;
  auto dt = compile_end-compile_start;
  cout<<"\033[34mTime taken to compile = "<<(int)dt<<" seconds.\033[0m"<<endl;

  gROOT->ProcessLine(processline);
}
