#!/bin/bash

#Setting parameters from outside:
outfile="skimFile.root" #Make sure that this name is identical to the one in crab_config
infile=$(python3 -c "import PSet; print(PSet.process.source.fileNames[0])")
campaign=$1
sample=$2
flag=$3

#Testing:
#infile="Skimmer/test_inputs/Muon_Run2022C.root"
#outfile="Skimmer/test_outputs/test_driver.root"
#campaign="Run3Summer22"
#sample="Data"
#flag="muon"

#root_command="compile_and_run.C(\"root://cms-xrd-global.cern.ch//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
root_command="compile_and_run.C(\"root://cmsxrootd.fnal.gov//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
#root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"


# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

root -q -b -l "$root_command"
