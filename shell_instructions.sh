#!/bin/bash

#Setting parameters from outside:
outfile="skimFile.root" #Make sure that this name is identical to the one in crab_config
infile=$(python3 -c "import PSet; print(PSet.process.source.fileNames[0])")
campaign=$1
sample=$2
flag=$3

#----------------- Testing block -----------------------
#file1="DYto2L-4Jets_MLL-50.root"
#file2="Muon_D_22Sep2023.root"
#file3="QCDEM_PT-10to30.root"
#infile="Skimmer/test_inputs/"$file1
#outfile="Skimmer/test_outputs/test_"$file1".root"
#campaign="Run3Summer22"
#sample="DY"
#flag="dy" #For data, flag = "muon" or "egamma"
#-------------------------------------------------------

#--------------- CRAB job failure ----------------------
#In case some CRAB jobs fail, bring those files manually.
#infile="/store/data/Run2022C/Muon/NANOAOD/22Sep2023-v1/30000/380e187b-1355-4cf6-8fa5-a818c004a4d9.root" #Failed, Muon_C, Run3Summer22
#outfile="skimFile_failed_22.root"
#campaign="Run3Summer22"
#sample="DY"
#flag="dy" #For data, flag = "muon" or "egamma"
#-------------------------------------------------------

#root_command="compile_and_run.C(\"root://cms-xrd-global.cern.ch//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
root_command="compile_and_run.C(\"root://cmsxrootd.fnal.gov//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
#root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"


# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

root -q -b -l "$root_command"
