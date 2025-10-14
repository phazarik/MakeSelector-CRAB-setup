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
	    TString infile  = "Skimmer/test_inputs/2017_UL_Muon_B_66_failed.root",
	    TString outfile = "Skimmer/test_outputs/skim_2017_UL_Muon_B_66_failed.root",
	    TString campaign = "2017_UL",
	    TString sample = "Data",
	    TString flag = "muon"
	    )
{

  TString sourceCodeDir = "Skimmer";  //Set code directory here.
  //TString sourceCodeDir = "TreeMaker";  //Set code directory here.
  
  TString arguments = "\""+infile+"\",\""+outfile+"\",\""+campaign+"\",\""+sample+"\",\""+flag+"\"";
  TString processline = ".x "+sourceCodeDir+"/run_locally.C(" + arguments + ")"; //testing purposes

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
