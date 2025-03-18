#---------------------------------------------
# CRAB SUBMISSION SETUP:
#
# Working example:
'''
crab submit crab_config.py \
General.requestName=nanoRDF_Run2_2017_UL_Rare_THQ \
General.workArea=submitted \
Data.inputDataset=/THQ_ctcvcp_4f_Hincl_TuneCP5_13TeV_madgraph_pythia8/RunIISummer20UL17NanoAODv9-106X_mc2017_realistic_v9-v2/NANOAODSIM
'''
#
# The following parameters fed from outside (bulksubmission)
# 1. General.requestName : This directory is created in the output area.
# 2. General.workArea : The crab-job logs are dumped in this folder, which is later used to monitor progress.
# 3. Data.inputDataset : Full DAS string of the input sample
# Rest of the parameters are same for all jobs, and are defined below.
#---------------------------------------------

from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config

config = config()

#-----------------------------------------------------------------------------
# Setting parameters:
import datetime,sys
timestamp = datetime.datetime.now().strftime("_%Y%m%d_%H%M%S")
datasetStr  = sys.argv[4]
datasetName = sys.argv[5]
samplename  = "DYToLL-4Jets_MLL-50"
flag        = "dy"
campaign    = "Run3Summer22"
print(f"submitting crab jobs for {datasetName}>> {datasetStr} \n")
##----------------------------------------------------------------------------

### General:
config.General.transferOutputs = True
config.General.transferLogs = True

### JobType:
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'crab_setup.sh'
config.JobType.inputFiles = [
    'PSet.py', 
    'compile_and_run.C', 
    'shell_instructions.sh',
    'includeHeaders.h',
    'Skimmer/AnaScript.C',
    'Skimmer/AnaScript.h',
    'Skimmer/AnaScript_C.so',
    'Skimmer/SkimmerHelper.h',
    'Setup/CustomFunctions.h',
    'Setup/ProduceGenCollection.h',
    'Setup/ProduceRecoCollection.h'
]
# Maintain the source directory structure
config.JobType.pyCfgParams = [
    f'campaign={campaign}',
    f'flag={flag}',
    f'samplename={samplename}'
]

config.JobType.outputFiles = ['skimFile.root']
#Make sure that this name is identical to the one in the shell script

### Data (input/output):
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1  # Number of files per job
config.Data.outLFNDirBase = '/store/user/phazarik/Run3_skim' #Customize here according to your needs.
config.Data.publication = False
config.Data.outputDatasetTag = f'run3Skim_{timestamp}'

### Site:
config.Site.storageSite = 'T3_CH_CERNBOX' #Customize here according to your needs.
