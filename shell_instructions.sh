#!/bin/bash

#Setting parameters using PSet.py
outfile="skimFile.root" #Make sure that this name is identical to the one in crab_config
infile=$(python3 -c "import PSet; print(PSet.process.source.fileNames[0])")
campaign=$(python3 -c "import PSet; print(PSet.process.custom_params.campaign_.value())")
flag=$(python3 -c "import PSet; print(PSet.process.custom_params.flag_.value())")
samplename=$(python3 -c "import PSet; print(PSet.process.custom_params.samplename_.value())")

#Testing:
#infile="Skimmer/test_inputs/DYto2L-4Jets_MLL-50.root"
#outfile="Skimmer/test_outputs/test_driver.root"
#campaign="Run3Summer22"
#sample="DYto2L-4Jets_MLL-50"
#flag="dy"

root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"

# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

#root -q -b -l "$root_command"
