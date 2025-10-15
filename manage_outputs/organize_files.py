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

campaign = "Run3Summer22EE"
inbase   = "/eos/user/p/phazarik/CRABDUMP"
outbase  = "/eos/user/p/phazarik/SKIMDUMP"
jobdir   = f"CRAB_skim_2L_Run3Summer22EE_2025-10-14"
dumpdir  = f"skimmed_2L_{campaign}_2025-10-14"
sample_file = f"../samplelists/{campaign}.txt"

# Job IDs for Data
job_ids_2016 = {

}
job_ids_2017={

}
job_ids_2018 = {
    "EGamma_A": "251006_055824",
    "EGamma_B": "251006_055830",
    "EGamma_C": "251006_055835", 
    "EGamma_D": "251006_055840",
    "Muon_A": "251006_055802",
    "Muon_B": "251006_055808",
    "Muon_C": "251006_055814",
    "Muon_D": "251006_055819"
}
job_ids_2022 = {
    "EGamma_C": "251015_085642",
    "EGamma_D": "251015_085647",
    "Muon_C": "251015_085630",
    "Muon_D": "251015_085635"
    "EGamma_F": "251014_135745",
    "EGamma_G": "251014_135750",
    "Muon_E": "251014_135646",
    "Muon_F": "251014_135651",
    "Muon_G": "251014_135655",
}
job_ids_2023 = {

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
