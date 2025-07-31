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
jobdir  = "CRAB_skim_2LSS_Run3Summer22EE_2025-08-01"
dumpdir = "skimmed_2LSS_Run3Summer22EE"
sample_file = '../samplelists/Run3Summer22EE.txt'

# Job IDs for Data
{
    #2022:
    "EGamma_E": "250731_175154",
    "EGamma_F": "250731_175202",
    "EGamma_G": "250731_175211",
    "Muon_E": "250731_175129",
    "Muon_F": "250731_175137",
    "Muon_G": "250731_175146"
}

with open(sample_file, 'r') as f: samples = ast.literal_eval(f.read())

# Process each sample
for fullsamplename, fulldasname, tag in samples:

    if ('Muon' in fullsamplename or 'EGamma' in fullsamplename): continue

    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')
    sample    = fullsamplename.split('_')[0]
    subsample = fullsamplename.split('_')[1]

    '''
    ###Exception:
    if "QCD_" in fullsamplename:
        sample    = fullsamplename.split('_')[0]+"_"+fullsamplename.split('_')[1]
        subsample = fullsamplename.split('_')[2]
    '''
    
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
