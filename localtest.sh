#!/bin/bash

# Test files :
# Skimmer/test_inputs/DYto2L_MLL-50_2022EE.root
# Skimmer/test_inputs/MuonE_2022EE.root
# Skimmer/test_inputs/QCDMu_80to120_2022EE.root
# /eos/home-p/phazarik/xrdcp_samples/RunIISummer20UL18NanoAODv9/VLLD_mu_M400_TuneCP5_13TeV-madgraph-pythia8/F54E0E1D-24AF-684D-9B5A-7FE4E37F018D.root
#--------------- CRAB job failure ----------------------

#In case some CRAB jobs fail, bring those files manually.
infile="Skimmer/test_inputs/MuonE_2022EE.root"
outfile="Skimmer/test_outputs/skim_$(basename $infile)"
#infile="Skimmer/test_outputs/skim_MuonE_2022EE.root"
#outfile="TreeMaker/test_outputs/tree_$(basename $infile)"
campaign="Run3Summer22EE"
sample="Muon"
flag="mc" #For data, flag = "muon" or "egamma"
maxevents=1000
#-------------------------------------------------------

#root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\")"
root_command="compile_and_run.C(\"$infile\", \"$outfile\", \"$campaign\", \"$sample\", \"$flag\", \"$maxevents\")"

# Echo the command for copy-paste testing
echo "Running ROOT command:"
echo "root -q -b -l '$root_command'"

root -q -b -l "$root_command"
