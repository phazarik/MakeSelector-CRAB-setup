#----------------------------------------------
# Submitting crab jobs in bulk.
#
# Note: Manage the parameters that are fed
# into crab_config.py according to your need.
#---------------------------------------------

import os,sys
import subprocess
import ast
import argparse
parser = argparse.ArgumentParser(description="Submit CRAB jobs in bulk.")
parser.add_argument("--test",   type=ast.literal_eval, default=False, help="Run only one sample. Pass True or False.")
parser.add_argument("--dryrun", type=ast.literal_eval, default=True,  help="Print the commands, don't run. Pass True or False.")
args = parser.parse_args()
args = parser.parse_args()

campaign = "Run3Summer23BPix"
test   = args.test
dryrun = args.dryrun

### Note: For data, use flag == 'muon' or 'egamma'

samples=[]
samplefile = f"samplelists/{campaign}.txt"
#samplefile = f"samplelists/failed_jobs.txt"
#samplefile = f"samplelists/training_{campaign}.txt"
#samplefile = f"samplelists/signal_{campaign}.txt"
with open(samplefile, "r") as file: content = file.read().strip()

samples = ast.literal_eval(content)

jobname ="nanoSkim_2023BPixdata"

# ------------------------------------------------------------------------------------
def check_voms_proxy():
    result = subprocess.run("voms-proxy-info --timeleft", shell=True, capture_output=True, text=True)
    time_left = result.stdout.strip()
    if result.returncode != 0 or not time_left.isdigit() or int(time_left) <= 0:
        print(f"\n{RED}[WARNING] CMS VOMS proxy not found or expired! Please run the following.{RESET}")
        print("voms-proxy-init -voms cms\n")
        return False
    return True

# ------------------------------------------------------------------------------------
def check_cmssw():
    cmssw_base = os.environ.get("CMSSW_BASE")
    if not cmssw_base:
        print(f"\n{RED}[WARNING] No CMSSW environment detected! Please set up CMSSW before running.{RESET}\n")
        return False
    return True

# ------------------------------------------------------------------------------------
if not check_cmssw() or not check_voms_proxy(): sys.exit(1)

count=0
for samplename, dataset, flag in samples:
    requestname = jobname + '_' + samplename
    
    ### Exceptions:
    #if "Muon" in samplename or "EGamma" in samplename: events = -1
    if not ('muon' in flag or 'egamma' in flag): continue
    #if "VLL" in samplename: continue
    #if ('QCDMu' in samplename) or ('QCDEle' in samplename): continue
    #if not ('QCD' in samplename or 'VLL' in samplename): continue
    
    ### Setting up the arguments for crab_config:
    arg3 = 'General.requestName=' + requestname # Name of the sub-directory in the output area.
    arg4 = 'Data.inputDataset='   + dataset     # Input DAS string
    arg5 = campaign
    arg6 = samplename
    arg7 = flag

    ### Verifying input DAS string:
    nfiles=0
    das_query = f'dasgoclient --query="file dataset={dataset}"'
    try:
        output = os.popen(das_query + " | wc -l").read().strip()
        if not output.isdigit(): raise ValueError("Invalid dasgoclient output")
        nfiles = int(output)
    except Exception as e:
        print(f'\033[31m[ERROR]\033[0m Failed to query DAS for {dataset}: {e}')
        continue

    ## Caclualte how many events to process per file.
    events_per_file = -1 ## all events
    #if events > 0: events_per_file = -(-events // nfiles) ## rounds up (ceiling division)
    
    ### Set ENV here
    os.environ['CRAB_CAMPAIGN']   = campaign
    os.environ['CRAB_SAMPLENAME'] = samplename
    os.environ['CRAB_FLAG']       = flag
    os.environ['CRAB_EVENTS']     = str(int(events_per_file))
    
    ### Main process line:
    processline = f'crab submit crab_config.py {arg3} {arg4}'

    count+=1
    print('-'*50)
    print(f'\n{count}. Processing \033[33m{dataset}\033[0m (nfiles = {nfiles})')

    print("\033[2;33m")
    print('export CRAB_CAMPAIGN='+campaign)
    print('export CRAB_SAMPLENAME='+samplename)
    print('export CRAB_FLAG='+flag)
    print('export CRAB_EVENTS='+str(int(events_per_file))+f" ## (per file, for {nfiles} files)\033[0m")
    if dryrun: print(processline)
    else: os.system(processline)
    if test: break

    # Working Example:
    # export CRAB_CAMPAIGN=Run3Summer22
    # export CRAB_SAMPLENAME=DYTo2L-4Jets_MLL-50
    # export CRAB_FLAG=dy
    # crab submit crab_config.py General.requestName=nanoSkim_DYTo2L-4Jets_MLL-50 Data.inputDataset=/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM 

print(f"\nDone!")
command = f"python3 {os.path.basename(__file__)} --dryrun False"
if dryrun: print(f"Run the following to submit:\n\033[93m{command}\033[0m\n")
else: print(f"Submitted {count} CRAB jobs.\n")
