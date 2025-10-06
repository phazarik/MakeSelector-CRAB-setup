//-------------------------------------------------------
// THIS SCRIPT RUNS IN ROOT PROMPT
// How to run :
// 1. Go to root prompt.
// 2. Compile and load the library: [].L AnaScript.C+
// 3. [].x run.C()
//-------------------------------------------------------

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>
#include <string>

void run(TString ifname, TString ofname, TString campaign, TString samplename, TString flag)
{
  //Description of the parameters:
  //1. ifname : Input file name with full path.
  //2. ofname : Output file name with full path.
  //3. data   : 0, or 1 depedning on whether 'ifname' is MC or data.
  //4. year   : Which year of data taking. (affects trigger paths and efficiencies)
  //5. lep    : If muon dataset, lep=1, if electron dataset, lep=0

  gErrorIgnoreLevel = kError;  // Suppress warnings (optional)
  TChain *chain = new TChain("Events");
  const char *outfilename;
  outfilename = ofname;

  //Loading the class:
  AnaScript m_selec;
  
  //Setting parameters:
  cout << "\033[33mInput  : " << ifname <<"\033[0m"<< endl;
  cout << "\033[33mOutput : " << ofname <<"\033[0m"<< endl;
  chain->Add(ifname);

  if (chain->GetListOfFiles()->GetEntries() == 0) {
    cout << "\033[1;31mERROR: No input files found or they could not be opened!\033[0m" << endl;
    return;
  }
  
  m_selec.SetTreeFileName(outfilename); //Don't forget to set this!
  m_selec.SetCampaign(campaign);
  m_selec.SetSampleName(samplename);
  m_selec.SetFlag(flag);
  if((flag == "egamma")||(flag =="muon")) m_selec.SetData(1);
  else m_selec.SetData(0);

  chain->Process(&m_selec);
  //cout<<"Done."<<endl;
}
