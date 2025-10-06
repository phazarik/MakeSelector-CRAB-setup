from WMCore.Configuration import Configuration
from CRABClient.UserUtilities import config

#-----------------------------------------------------------------------------
# Setting parameters:
import datetime,os,sys
timestamp  = datetime.datetime.now().strftime("_%Y%m%d_%H%M%S")
campaign   = os.getenv('CRAB_CAMPAIGN', 'Run3Summer22')
samplename = os.getenv('CRAB_SAMPLENAME', 'DYTo2L-4Jets_MLL-50')
flag       = os.getenv('CRAB_FLAG', 'dy')
print(f'Samplename={samplename} campaign={campaign} flag={flag}')
##----------------------------------------------------------------------------

config = config()

### General:
config.General.transferOutputs = True
config.General.transferLogs = True
#config.General.requestName=reqname ### Taken from argument
config.General.workArea='submitted'

### JobType:
config.JobType.pluginName = 'Analysis'
config.JobType.psetName   = 'PSet.py'
config.JobType.scriptExe  = 'crab_script.sh'
config.JobType.scriptArgs = [f"campaign={campaign}", f"sample={samplename}", f"flag={flag}"]
config.JobType.inputFiles = [
    'compile_and_run.C', 
    'shell_instructions.sh',
    'includeHeaders.h',
    'FrameworkJobReport.xml',
    'Skimmer/AnaScript.C',
    'Skimmer/run_locally.C',
    'Skimmer/AnaScript.h',
    'Skimmer/SkimmerHelper.h',
    'Setup/CustomFunctions.h',
    'Setup/ProduceGenCollection.h',
    'Setup/ProduceRecoCollection.h',
    'Setup/veto3L4L.h'
]
config.JobType.outputFiles = ['skimFile.root']
#Make sure that this name is identical to the one in the shell script

### Data (input/output):
#config.Data.inputDataset = dasname ### Taken from argument
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1  # Number of files per job
config.Data.outLFNDirBase = '/store/user/phazarik/CRAB_skim_2LOS_2018_UL_2025-10-06'
config.Data.publication = False
config.Data.outputDatasetTag = f'skimmed' ###subdirectory

### Site:
config.Site.storageSite = 'T3_CH_CERNBOX' #Customize here according to your needs.
