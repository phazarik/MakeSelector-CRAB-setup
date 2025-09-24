#!/bin/bash
### Setting parameters from outside:
outfile="skimFile.root" #Make sure that this name is identical to the one in crab_config
infile=$(python3 -c "import PSet; print(PSet.process.source.fileNames[0])")
campaign=$1
sample=$2
flag=$3

#root_command="compile_and_run.C(\"root://cms-xrd-global.cern.ch//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
root_command="compile_and_run.C(\"root://cmsxrootd.fnal.gov//$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"

# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

root -q -b -l "$root_command"
