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
jobdir  = "Run3Summer22_skim_Datav12"
dumpdir = "skimmed_2LSS_Run3Summer22_v12"

# Job IDs for Data
job_ids = {
    "EGamma_C": "250418_093035",
    "EGamma_D": "250418_093040",
    "Muon_C": "250418_093023",
    "Muon_D": "250418_093030"
}

sample_file = '../samplelist_run3summer22.txt'
with open(sample_file, 'r') as f: samples = ast.literal_eval(f.read())

# Process each sample
for fullsamplename, fulldasname, tag in samples:
    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')
    sample    = fullsamplename.split('_')[0]
    subsample = fullsamplename.split('_')[1]
    dump = os.path.join(basedir, dumpdir, sample, subsample)
    dasname = fulldasname.split('/')[1]
    searchdir = os.path.join(basedir, jobdir, dasname)

    if not dryrun: os.makedirs(dump, exist_ok=True)

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
                if not dryrun: os.system(f'cp {src} {dst}')
                if dryrun: print(f"{nfile} {command}", style="dim")

            print(f'Copied {nfile} files to {dump}', style='yellow')

    if not files_found: print(f'WARNING: No root files in: {searchdir}, skipping.', style='red')
    if test: break  ## Sample

print(f'\nAll files in {jobdir} copied to {dumpdir}\n', style='Yellow bold')
