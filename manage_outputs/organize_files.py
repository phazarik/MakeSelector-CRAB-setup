import os, sys
import ast
import argparse
import time
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
test   = args.test
dryrun = args.dryrun

if test:   print('[WARNING]: test mode',   style="red")
if dryrun: print('[WARNING]: dryrun mode', style="red")
print()

basedir = "/eos/user/p/phazarik"
jobdir  = "skim_forTraining_2018_UL"
dumpdir = "skimmed_forTraining_2018_UL"
sample_file = '../samplelists/2018_UL.txt'

# Job IDs for Data
job_ids = {
    "EGamma0_C1": "250618_102251",
    "EGamma0_C2": "250618_102258",
    "EGamma0_C3": "250618_102306",
    "EGamma0_C4": "250618_102316",
    "EGamma1_C1": "250618_102324",
    "EGamma1_C2": "250618_102332",
    "EGamma1_C3": "250618_102342",
    "EGamma1_C4": "250618_102353",
    "Muon0_C1": "250618_102155",
    "Muon0_C2": "250618_102201",
    "Muon0_C3": "250618_102216",
    "Muon0_C4": "250618_102221",
    "Muon1_C1": "250618_102227",
    "Muon1_C2": "250618_102233",
    "Muon1_C3": "250618_102240",
    "Muon1_C4": "250618_102245"
}

with open(sample_file, 'r') as f: samples = ast.literal_eval(f.read())

# Process each sample
for fullsamplename, fulldasname, tag in samples:

    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')
    sample    = fullsamplename.split('_')[0]
    subsample = fullsamplename.split('_')[1]

    ###Exception:
    if "QCD_" in fullsamplename:
        sample    = fullsamplename.split('_')[0]+"_"+fullsamplename.split('_')[1]
        subsample = fullsamplename.split('_')[2]

    dump = os.path.join(basedir, dumpdir, sample, subsample)
    dasname = fulldasname.split('/')[1]
    searchdir = os.path.join(basedir, jobdir, dasname)

    ### Exception for data:
    if fullsamplename in job_ids:
        job_id = job_ids[fullsamplename]
        searchdir = os.path.join(basedir, jobdir, sample, "run3Skim", job_id)

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
                    os.system(f'cp {src} {dst}')
                if dryrun: print(f"{nfile} {command}", style="dim")

            print(f'Copied {nfile} files to {dump}', style='yellow')

    if not files_found: print(f'WARNING: No root files in: {searchdir}, skipping.', style='red')
    if test: break  ## Sample

print(f'\nAll files in {jobdir} copied to {dumpdir}\n', style='Yellow bold')
