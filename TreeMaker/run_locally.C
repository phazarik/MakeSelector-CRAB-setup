//----------------------------
// Test-run on a single file
//----------------------------

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <string>
using namespace std;

void run_locally(
		 TString infile  = "test_inputs/DYto2L-4Jets_MLL-50.root",
		 TString outfile = "test_outputs/skimtest.root",
		 TString campaign = "Run3Summer22",
		 TString sample = "DYJetsToLL_M50",
		 TString flag = "dy"
		 )
{
  // Suppress warnings (optional)
  gErrorIgnoreLevel = kError;
  
  TChain *chain = new TChain("Events");
  AnaScript m_selec;
  const char *treefilename;
  treefilename = outfile;
  
  //Parameter set:
  cout << "\033[33mInput  : " << infile <<"\033[0m"<< endl;
  cout << "\033[33mOutput : " << outfile <<"\033[0m"<< endl;
  chain->Add(infile);
  m_selec.SetTreeFileName(treefilename);
  m_selec.SetCampaign(campaign);
  m_selec.SetSampleName(sample);

  //Override parameters:
  if(sample.Contains("Muon")  || sample.Contains("EGamma")) flag = "muon";
  if(sample.Contains("QCDMu") || sample.Contains("QCDEM"))  flag = "qcd";

  m_selec.SetFlag(flag);
  if((flag == "egamma")||(flag =="muon")) m_selec.SetData(1);
  else m_selec.SetData(0);
  
  chain->Process(&m_selec);
  cout<<"Done."<<endl;
}
