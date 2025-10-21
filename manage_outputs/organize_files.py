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

campaign = "2016postVFP_UL"
inbase   = "/eos/user/p/phazarik/CRABDUMP"
outbase  = "/eos/user/p/phazarik/SKIMDUMP"
jobdir   = f"CRAB_skim_2L_2016postVFP_UL_2025-10-20"
dumpdir  = f"skimmed_2L_{campaign}_2025-10-21"
sample_file = f"../samplelists/{campaign}.txt"

# Job IDs for Data
job_ids_2016 = {
    "EGamma_F": "251020_072350",
    "EGamma_G": "251020_072355",
    "EGamma_H": "251020_072359",
    "Muon_F": "251020_072336",
    "Muon_G": "251020_072341",
    "Muon_H": "251020_072346",
    "EGamma_B1": "251020_063656",
    "EGamma_B2": "251020_063701",
    "EGamma_C": "251020_063706",
    "EGamma_D": "251020_063710",
    "EGamma_E": "251020_063714",
    "EGamma_FHIPM": "251020_063719",
    "Muon_B1": "251020_063629",
    "Muon_B2": "251020_063634",
    "Muon_C": "251020_063638",
    "Muon_D": "251020_063643",
    "Muon_E": "251020_063648",
    "Muon_FHIPM": "251020_063652"
}
job_ids_2017={
    "Muon_B": "251019_183237",
    "Muon_C": "251019_183242",
    "Muon_D": "251019_183248",
    "Muon_E": "251019_183253",
    "Muon_F": "251019_183259",
    "EGamma_B": "251019_183304",
    "EGamma_C": "251019_183309",
    "EGamma_D": "251019_183314",
    "EGamma_E": "251019_183319",
    "EGamma_F": "251019_183324"
}
job_ids_2018 = {
    "EGamma_A": "251019_132621",
    "EGamma_B": "251019_132627",
    "EGamma_C": "251019_132632",
    "EGamma_D": "251019_132637",
    "Muon_A": "251019_132600",
    "Muon_B": "251019_132605",
    "Muon_C": "251019_132610",
    "Muon_D": "251019_132616"
}
job_ids_2022 = {
    "Muon_E": "251017_110652",
    "Muon_F": "251017_110657",
    "Muon_G": "251017_110702",
    "Muon_C": "251017_111019",
    "Muon_D": "251017_111026",
    "EGamma_E": "251021_170710",
    "EGamma_F": "251021_170718",
    "EGamma_G": "251021_170725",
    "EGamma_C": "251021_170838",
    "EGamma_D": "251021_170845"
}
job_ids_2023 = {
    "Muon0_D1": "251017_123837",
    "Muon0_D2": "251017_123842",
    "Muon1_D1": "251017_123848",
    "Muon1_D2": "251017_123853",
    "Muon0_C1": "251017_123324",
    "Muon0_C2": "251017_123330",
    "Muon0_C3": "251017_123335",
    "Muon0_C4": "251017_123340",
    "Muon1_C1": "251017_123346",
    "Muon1_C2": "251017_123352",
    "Muon1_C3": "251017_123357",
    "Muon1_C4": "251017_123402",
    "EGamma0_D1": "251021_171847",
    "EGamma0_D2": "251021_171117",
    "EGamma1_D1": "251021_171123",
    "EGamma1_D2": "251021_171129",
    "EGamma0_C1": "251021_170933",
    "EGamma0_C2": "251021_170940",
    "EGamma0_C3": "251021_170946",
    "EGamma0_C4": "251021_170952",
    "EGamma1_C1": "251021_170958",
    "EGamma1_C2": "251021_171005",
    "EGamma1_C3": "251021_171011",
    "EGamma1_C4": "251021_171017"
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
