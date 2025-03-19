from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config

config = config()

#-----------------------------------------------------------------------------
# Setting parameters:
import datetime,sys
timestamp = datetime.datetime.now().strftime("_%Y%m%d_%H%M%S")
campaign    = "Run3Summer22"
samplename  = "DYToLL-4Jets_MLL-50"
flag        = "dy"
##----------------------------------------------------------------------------

### General:
config.General.transferOutputs = True
config.General.transferLogs = True
config.General.requestName='nanoskim_test4'
config.General.workArea='submitted'

### JobType:
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'PSet.py'
config.JobType.scriptExe = 'crab_script.sh'
config.JobType.scriptArgs = [f"campaign={campaign}", f"sample={samplename}", f"flag={flag}"]
config.JobType.inputFiles = [
    'compile_and_run.C', 
    'shell_instructions.sh',
    'includeHeaders.h',
    'FrameworkJobReport.xml',
    'Skimmer/AnaScript.C',
    'Skimmer/run_locally.C',
    'Skimmer/AnaScript.h',
    #'Skimmer/AnaScript_C.so',
    'Skimmer/SkimmerHelper.h',
    'Setup/CustomFunctions.h',
    'Setup/ProduceGenCollection.h',
    'Setup/ProduceRecoCollection.h'
]
config.JobType.outputFiles = ['skimFile.root']
#Make sure that this name is identical to the one in the shell script

### Data (input/output):
config.Data.inputDataset='/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1  # Number of files per job
config.Data.outLFNDirBase = '/store/user/phazarik/Run3_skim' #Customize here according to your needs.
config.Data.publication = False
config.Data.outputDatasetTag = f'run3Skim_{timestamp}'

### Site:
config.Site.storageSite = 'T3_CH_CERNBOX' #Customize here according to your needs.
