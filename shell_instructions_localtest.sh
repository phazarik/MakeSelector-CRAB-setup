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
file4="QCD_MuEnriched_120to170_2018_UL.root"
infile="Skimmer/test_inputs/"$file4
outfile="Skimmer/test_outputs/test_"$file4".root"
campaign="2018_UL"
sample="QCD"
flag="qcd" #For data, flag = "muon" or "egamma"
#-------------------------------------------------------

#--------------- CRAB job failure ----------------------
#In case some CRAB jobs fail, bring those files manually.
#infile="/store/data/Run2022C/Muon/NANOAOD/22Sep2023-v1/30000/380e187b-1355-4cf6-8fa5-a818c004a4d9.root" #Failed, Muon_C, Run3Summer22
#infile="/store/data/Run2022E/Muon/NANOAOD/22Sep2023-v1/2540000/e662055f-50db-443c-9a00-006ac7b33f15.root" #Failed, Muon_E, Run3Summer22EE
#infile="EGamma_F_454.root"
#outfile="skimFile_failed_22.root"
#outfile="skimFile_failed_Run3Summer22EE_EGammaF_454.root"
#campaign="Run3Summer22"
#sample="Muon_E"
#flag="muon" #For data, flag = "muon" or "egamma"
#-------------------------------------------------------

root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
#root_command="compile_and_run.C(\"root://cms-xrd-global.cern.ch//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
#root_command="compile_and_run.C(\"root://cmsxrootd.fnal.gov//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"

# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

root -q -b -l "$root_command"
