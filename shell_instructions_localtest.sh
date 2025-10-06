#!/bin/bash
### Setting parameters from outside:
#outfile="skimFile.root" #Make sure that this name is identical to the one in crab_config
#infile=$(python3 -c "import PSet; print(PSet.process.source.fileNames[0])")
#campaign=$1
#sample=$2
#flag=$3

#----------------- Testing block -----------------------
#file1="Run3Summer23_DYto2L-4Jets_MLL-50.root"
#file2="Muon_D_22Sep2023.root"
#file3="QCDEM_PT-10to30.root"
#file4="QCD_MuEnriched_120to170_2018_UL.root"
#infile="Skimmer/test_inputs/"$file4
#outfile="Skimmer/test_outputs/test_"$file4".root"
#campaign="2018_UL"
#sample="QCD"
#flag="qcd" #For data, flag = "muon" or "egamma"
#-------------------------------------------------------

#--------------- CRAB job failure ----------------------
#In case some CRAB jobs fail, bring those files manually.
infile="/eos/home-p/phazarik/xrdcp_samples/RunIISummer20UL18NanoAODv9/VLLD_ele_M100_TuneCP5_13TeV-madgraph-pythia8/A61B7946-A810-F64A-A712-835B943C287B.root"
outfile="skimFile_VLLD_ele_M100.root"
campaign="2018_UL"
sample="VLLD_ele_M100"
flag="doublet" #For data, flag = "muon" or "egamma"
#-------------------------------------------------------

root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
#root_command="compile_and_run.C(\"root://cms-xrd-global.cern.ch//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
#root_command="compile_and_run.C(\"root://cmsxrootd.fnal.gov//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"

# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

root -q -b -l "$root_command"
