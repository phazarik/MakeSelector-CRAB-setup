#!/bin/bash

# Picking up argumnets given in key=value format.
for ARGUMENT in "$@"
do
    if [[ "$ARGUMENT" == *"="* ]]; then
	KEY=$(echo $ARGUMENT | cut -f1 -d=)
	VALUE="${ARGUMENT#*=}"
	export "$KEY"="$VALUE"
    fi
done

#Set up CMS environment
source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=el8_amd64_gcc12
#eval `scramv1 project CMSSW CMSSW_14_1_0_pre4`
eval $(scramv1 project CMSSW CMSSW_14_1_0_pre4)
cd CMSSW_14_1_0_pre4/src
#eval `scramv1 runtime -sh`
eval $(scramv1 runtime -sh)
cd ../../
echo "Current directory: $(pwd)"
echo "Contents of this directory:"
ls -l $PWD

echo "Creating necessary directories..."
mkdir -p Skimmer
mkdir -p Setup

echo "Moving files to respective directories..."
mv AnaScript.C Skimmer/
mv AnaScript.h Skimmer/
mv SkimmerHelper.h Skimmer/
mv run_locally.C Skimmer/
mv CustomFunctions.h Setup/
mv ProduceGenCollection.h Setup/
mv ProduceRecoCollection.h Setup/

echo "Verifying the directory structure after moving files..."
ls -l Skimmer
ls -l Setup

# Load PSet and display the input files
echo "================= Dumping Input files ===================="
#python3 -c "import PSet; print ('\n'.join(list(PSet.process.source.fileNames)))"
python3 -c "import PSet; print('\n'.join(list(PSet.process.source.fileNames)))"
echo "Other parameters from crab_config.py: "
echo "campaign = "$campaign
echo "sample = "$sample
echo "flag = "$flag
echo "=========================================================="

# Run the shell_instructions.sh, which will use the parameters directly from PSet
bash shell_instructions.sh "$campaign" "$sample" "$flag"
