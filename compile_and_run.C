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
		     TString infile = "Skimmer/test_inputs/EGamma_E_2022EE.root",
		     //TString infile  = "Skimmer/test_inputs/VLLD-mu_400_2018.root",
		     //TString infile  = "TreeMaker/test_inputs/*.root",
		     TString outfile = "Skimmer/test_outputs/test.root",
		     //TString infile = "FailedJobs/File_204_stuck.root",
		     //TString outfile = "FailedJobs/skimFile_204_stuck.root",
		     TString campaign = "Run3Summer22EE",
		     TString sample = "EGamma_C",
		     TString flag = "egamma",
		     TString maxevents = "-1" //Used only in the skimmer; -1 = all
	    )
{

  //Skimmer setup:
  TString sourceCodeDir = "Skimmer";  //Set code directory here.
  TString arguments = "\""+infile+"\",\""+outfile+"\",\""+campaign+"\",\""+sample+"\",\""+flag+"\",\""+maxevents+"\"";
  
  //TreeMaker setup:
  //TString sourceCodeDir = "TreeMaker";  //Set code directory here.
  //TString arguments = "\""+infile+"\",\""+outfile+"\",\""+campaign+"\",\""+sample+"\",\""+flag+"\"";
  
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
