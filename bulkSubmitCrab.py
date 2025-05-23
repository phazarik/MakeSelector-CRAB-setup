#----------------------------------------------
# Submitting crab jobs in bulk.
#
# Note: Manage the parameters that are fed
# into crab_config.py according to your need.
#---------------------------------------------

import os,sys
import ast

campaign = "Run3Summer22EE"
test   = False
dryrun = False

### Note: For data, use flag == 'muon' or 'egamma'

samples=[]
with open("samplelists/Run3Summer22EE.txt", "r") as file: content = file.read().strip()

samples = ast.literal_eval(content)

jobname ="nanoSkim_Run3"

count=0
for samplename, dataset, flag in samples:
    requestname = jobname + '_' + samplename

    ### Exceptions:
    if 'muon' in flag or 'egamma' in flag: continue
    #if not ('QCDMu' in samplename) or ('QCDEle' in samplename): continue
    #if not 'QCD' in samplename: continue
    
    ### Setting up the arguments for crab_config:
    arg3 = 'General.requestName=' + requestname # Name of the sub-directory in the output area.
    arg4 = 'Data.inputDataset='   + dataset     # Input DAS string
    arg5 = campaign
    arg6 = samplename
    arg7 = flag

    ### Set ENV here
    os.environ['CRAB_CAMPAIGN'] = campaign
    os.environ['CRAB_SAMPLENAME'] = samplename
    os.environ['CRAB_FLAG'] = flag
    
    ### Main process line:
    processline = f'crab submit crab_config.py {arg3} {arg4}'

    count+=1
    print('-'*50)
    print(f'\n{count}. Processing \033[33m{dataset}\033[0m')
    if dryrun :
        print('export CRAB_CAMPAIGN='+campaign)
        print('export CRAB_SAMPLENAME='+samplename)
        print('export CRAB_FLAG='+flag)
        print(processline)
    else: os.system(processline)
    if test: break

    # Working Example:
    # export CRAB_CAMPAIGN=Run3Summer22
    # export CRAB_SAMPLENAME=DYTo2L-4Jets_MLL-50
    # export CRAB_FLAG=dy
    # crab submit crab_config.py General.requestName=nanoSkim_DYTo2L-4Jets_MLL-50 Data.inputDataset=/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM 

print(f"\nDone! Submitted {count} CRAB jobs.\n")
