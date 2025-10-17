import os
import ast
import argparse
from datetime import date
from tqdm import tqdm
from rich.console import Console

# Setup the console for rich printing
console = Console(highlight=False)
print = console.print

# Argument parsing for test and dryrun options
parser = argparse.ArgumentParser()
parser.add_argument('--test', action='store_true')
parser.add_argument('--dryrun', action='store_true')
args = parser.parse_args()
test = args.test
dryrun = args.dryrun

if test:   print('[WARNING]: test mode', style="red")
if dryrun: print('[WARNING]: dryrun mode', style="red")
print()

campaign = "2018_UL"
inbase   = "/eos/user/p/phazarik/CRABDUMP"
outbase  = "/eos/user/p/phazarik/SKIMDUMP"
jobdir   = f"CRAB_skim_2L_2018_UL_2025-10-16"
dumpdir  = f"skimmed_2L_{campaign}_2025-10-17"
sample_file = f"../samplelists/{campaign}.txt"

# Job IDs for Data
job_ids_2016 = {

}
job_ids_2017={

}
job_ids_2018 = {
    "EGamma_A": "251017_045621",
    "EGamma_B": "251017_045626",
    "EGamma_C": "251017_045631",
    "EGamma_D": "251017_045636",
    "Muon_A": "251017_045559",
    "Muon_B": "251017_045604",
    "Muon_C": "251017_045610",
    "Muon_D": "251017_045615"
}
job_ids_2022 = {
    "EGamma_E": "251017_110708",
    "EGamma_F": "251017_110716",
    "EGamma_G": "251017_110724",
    "Muon_E": "251017_110652",
    "Muon_F": "251017_110657",
    "Muon_G": "251017_110702",
    "EGamma_C": "251017_111032",
    "EGamma_D": "251017_111038",
    "Muon_C": "251017_111019",
    "Muon_D": "251017_111026"
}
job_ids_2023 = {
    "EGamma0_D1": "251017_123859",
    "EGamma0_D2": "251017_123904",
    "EGamma1_D1": "251017_123909",
    "EGamma1_D2": "251017_123915",
    "Muon0_D1": "251017_123837",
    "Muon0_D2": "251017_123842",
    "Muon1_D1": "251017_123848",
    "Muon1_D2": "251017_123853",
    "EGamma0_C1": "251017_123407",
    "EGamma0_C2": "251017_123413",
    "EGamma0_C3": "251017_123418",
    "EGamma0_C4": "251017_123424",
    "EGamma1_C1": "251017_123429",
    "EGamma1_C2": "251017_123435",
    "EGamma1_C3": "251017_123440",
    "EGamma1_C4": "251017_123446",
    "Muon0_C1": "251017_123324",
    "Muon0_C2": "251017_123330",
    "Muon0_C3": "251017_123335",
    "Muon0_C4": "251017_123340",
    "Muon1_C1": "251017_123346",
    "Muon1_C2": "251017_123352",
    "Muon1_C3": "251017_123357",
    "Muon1_C4": "251017_123402"
}

job_ids = {}
if "2016"     in campaign: job_ids = job_ids_2016
if "2017"     in campaign: job_ids = job_ids_2017
if "2018"     in campaign: job_ids = job_ids_2018
if "Summer22" in campaign: job_ids = job_ids_2022
if "Summer23" in campaign: job_ids = job_ids_2023 

with open(sample_file, 'r') as f: samples = ast.literal_eval(f.read())

# Process each sample
for fullsamplename, fulldasname, tag in samples:
    sample = fullsamplename.split('_')[0]
    subsample = fullsamplename.split('_')[1] if '_' in fullsamplename else ''
    foldername = sample

    #if not ("QCD" in sample or "VLL" in sample): continue
    ### Exceptions:
    #if not ("Muon" in fullsamplename or "EGamma" in fullsamplename): continue
    if "Run3" not in campaign and 'Muon' in sample: foldername = 'SingleMuon'
    if "Run3" not in campaign and 'EGamma' in sample and '2018' not in campaign: foldername = 'SingleElectron'
    
    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')

    # Output directory
    dump = os.path.join(outbase, dumpdir, sample, subsample) if subsample else os.path.join(outbase, dumpdir, sample)

    # Input directory
    if 'Muon' in fullsamplename or 'EGamma' in fullsamplename:
        if fullsamplename in job_ids:
            job_id = job_ids[fullsamplename]
            #searchdir = os.path.join(inbase, jobdir, foldername, "run3Skim", job_id)
            searchdir = os.path.join(inbase, jobdir, foldername, "skimmed", job_id)
        else:
            print(f'WARNING: {fullsamplename} not in job_ids. Skipping.', style="red")
            continue
    else:
        # For MC samples, use the dasname
        dasname = fulldasname.split('/')[1]
        searchdir = os.path.join(inbase, jobdir, dasname)

    if not os.path.exists(searchdir):
        print(f'WARNING: Path does not exist: {searchdir}. Skipping.', style="red")
        continue

    print(f'Searching files in: {searchdir}')

    files_found = False
    for rootdir, _, files in os.walk(searchdir):
        root_files = [f for f in files if f.endswith('.root')]
        if root_files:
            print(f'Found {len(root_files)} root files in: {rootdir}')
            files_found = True
            nfile = 0
            for file in root_files:
                nfile += 1
                src = os.path.join(rootdir, file)
                dst = os.path.join(dump, file)
                command = f'cp {src} {dst}'
                if not dryrun:
                    os.makedirs(dump, exist_ok=True)
                    os.system(command)
                if dryrun: print(f"{nfile} {command}", style="dim")
                if dryrun: break

            print(f'Copied {nfile} files to {dump}', style='yellow')

    if not files_found: print(f'WARNING: No root files in: {searchdir}, skipping.', style='red')
    if test: break  # Process only one sample in test mode

print(f'\nAll files in {jobdir} copied to {dumpdir}\n', style='yellow bold')
