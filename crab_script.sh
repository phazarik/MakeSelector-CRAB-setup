#!/bin/bash

#Set up CMS environment
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=el8_amd64_gcc12
eval `scramv1 project CMSSW CMSSW_14_1_0_pre4`
cd CMSSW_14_1_0_pre4/src
eval `scramv1 runtime -sh`
cd ../../
echo "Current directory: $(pwd)"


# Load PSet and display the input files
echo "================= Dumping Input files ===================="
python3 -c "import PSet; print ('\n'.join(list(PSet.process.source.fileNames)))"
echo "=========================================================="

# Run the shell_instructions.sh, which will use the parameters directly from PSet
bash shell_instructions.sh
