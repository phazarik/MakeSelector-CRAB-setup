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
basedir  = "/eos/user/p/phazarik"
jobdir   = f"CRAB_skim_2LOS_2018_UL_2025-10-06"
#jobdir   = f"CRAB_skim_2LSS_{campaign}_forTraining"
dumpdir  = f"skimmed_2LOS_{campaign}_2025-10-06"
#dumpdir  = f"training_2LSS_{campaign}"
sample_file = f"../samplelists/{campaign}.txt"

# Job IDs for Data
job_ids_2016 = {
    "EGamma_B1": "250806_110227",
    "EGamma_B2": "250806_110233",
    "EGamma_C":  "250806_110239",
    "EGamma_D":  "250806_110244",
    "EGamma_E":  "250806_110250",
    "EGamma_FHIPM": "250806_110256",
    "EGamma_F":  "250806_111437",
    "EGamma_G":  "250806_111442",
    "EGamma_H":  "250806_111447",
    "Muon_B1": "250806_110150",
    "Muon_B2": "250806_110157",
    "Muon_C":  "250806_110203",
    "Muon_D":  "250806_110209",
    "Muon_E":  "250806_110216",
    "Muon_FHIPM": "250806_110221",
    "Muon_F":  "250806_111418",
    "Muon_G":  "250806_111424",
    "Muon_H":  "250806_111430"
}
job_ids_2017={
    "EGamma_B": "250810_145146",
    "EGamma_C": "250810_145152",
    "EGamma_D": "250810_145157",
    "EGamma_E": "250810_145202",
    "EGamma_F": "250810_145207",
    "Muon_B": "250810_145130",
    "Muon_C": "250810_145046",
    "Muon_D": "250810_145052",
    "Muon_E": "250810_145057",
    "Muon_F": "250810_145103"
}
job_ids_2018 = {
    "EGamma_A": "251006_132331",
    "EGamma_B": "251006_132337",
    "EGamma_C": "251006_132344",
    "EGamma_D": "251006_132351",
    "Muon_A": "251006_132306",
    "Muon_B": "251006_132313",
    "Muon_C": "251006_132319",
    "Muon_D": "251006_132325",
}
job_ids_2022 = {
    "EGamma_C": "250801_091720",
    "EGamma_D": "250801_091725",
    "EGamma_E": "250731_175154",
    "EGamma_F": "250731_175202",
    "EGamma_G": "250731_175211",
    "Muon_C": "250801_091710",
    "Muon_D": "250801_091715",
    "Muon_E": "250731_175129",
    "Muon_F": "250731_175137",
    "Muon_G": "250731_175146"
}
job_ids_2023 = {
    "EGamma0_C1": "250802_134637",
    "EGamma0_C2": "250802_134642",
    "EGamma0_C3": "250802_134647",
    "EGamma0_C4": "250802_134652",
    "EGamma0_D1": "250802_134819",
    "EGamma0_D2": "250802_134824",
    "EGamma1_C1": "250802_134657",
    "EGamma1_C2": "250802_134702",
    "EGamma1_C3": "250802_134707",
    "EGamma1_C4": "250802_134712",
    "EGamma1_D1": "250802_134829",
    "EGamma1_D2": "250802_134835",
    "Muon0_C1": "250802_134557",
    "Muon0_C2": "250802_134602",
    "Muon0_C3": "250802_134608",
    "Muon0_C4": "250802_134613",
    "Muon0_D1": "250802_134759",
    "Muon0_D2": "250802_134804",
    "Muon1_C1": "250802_134617",
    "Muon1_C2": "250802_134622",
    "Muon1_C3": "250802_134627",
    "Muon1_C4": "250802_134632",
    "Muon1_D1": "250802_134809",
    "Muon1_D2": "250802_134814"
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
    
    ### Exceptions:
    #if not ("Muon" in fullsamplename or "EGamma" in fullsamplename): continue
    if "Run3" not in campaign and 'Muon' in sample: foldername = 'SingleMuon'
    if "Run3" not in campaign and 'EGamma' in sample and '2018' not in sample: foldername = 'SingleElectron'
    
    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')

    # Output directory
    dump = os.path.join(basedir, dumpdir, sample, subsample) if subsample else os.path.join(basedir, dumpdir, sample)

    # Input directory
    if 'Muon' in fullsamplename or 'EGamma' in fullsamplename:
        if fullsamplename in job_ids:
            job_id = job_ids[fullsamplename]
            #searchdir = os.path.join(basedir, jobdir, foldername, "run3Skim", job_id)
            searchdir = os.path.join(basedir, jobdir, foldername, "skimmed", job_id)
        else:
            print(f'WARNING: {fullsamplename} not in job_ids. Skipping.', style="red")
            continue
    else:
        # For MC samples, use the dasname
        dasname = fulldasname.split('/')[1]
        searchdir = os.path.join(basedir, jobdir, dasname)

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
