import os, sys
import time
from datetime import timedelta
start_time = time.time()

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--dryrun', action='store_true', help='Check if everything is correct before submitting')
parser.add_argument('--test', action='store_true', help='Check one job')
args=parser.parse_args()


jobname = "skimmed_2LSS_2018_UL_2025-10-06"
outdir  = "tree_2LSS_baseline_2018_UL"
campaign = "2018_UL"

outdir  = os.path.join("/eos/user/p/phazarik/", outdir)
indir   = os.path.join("/eos/user/p/phazarik/", jobname)
samples = os.listdir(indir)
if not args.dryrun: os.makedirs(outdir, exist_ok=True)

hline = "-"*30
njobs = 0
nfiles= 0
list_processed=[]

for sample in samples:
    if not os.path.isdir(os.path.join(indir, sample)): continue
    subsamples = os.listdir(os.path.join(indir, sample))

    print("\n"+hline)
    print(f"\033[93mProcessing {sample}\033[0m")
    print(hline+"\n")

    flag = "mc"
    if 'Muon' in sample:    flag='muon'
    if 'EGamma' in sample:  flag='egamma'
    if sample == 'QCDMu' :  flag='qcd'
    if sample == 'QCDEle' : flag='qcdele'
    if sample == 'DYto2L':  flag='dy'
    if sample == 'TT':      flag='ttbar'
    if 'VLLD' in sample:    flag='doublet'

    sample_time_start = time.time()
    
    for subsample in subsamples:
        if not os.path.isdir(os.path.join(indir, sample, subsample)): continue

        fullsamplename = f"{sample}_{subsample}"
        print(f'\n\033[94mProcessing {fullsamplename} ... \033[0m')
        
        infiledir = os.path.join(indir, sample, subsample)
        nfiles += len(os.listdir(infiledir))
        infiles = os.path.join(infiledir, "*root")
        outfile = os.path.join(outdir, f"tree_{fullsamplename}.root")

        rootmacro = "TreeMaker/compile_and_run.C"
        arguments = f'"{infiles}", "{outfile}", "{campaign}", "{fullsamplename}", "{flag}"'
        command = f"root -q -b -l '{rootmacro}({arguments})'"

        if args.dryrun: print(f"\033[33m{command}\033[0m")
        
        njobs += 1
        sample_time_end=time.time()
        sample_time = sample_time_end-sample_time_start
        print(f'\nJob succeeded for {fullsamplename}')
        print(f'Time taken for this sample = {int(sample_time)} seconds.')
        list_processed.append(fullsamplename)
        sample_time_start = sample_time_end

        if args.test: break ##subsample
    if args.test: break ##sample

end_time = time.time()
time_taken = end_time-start_time
time_fmt = str(timedelta(seconds=int(time_taken)))

print("\033[93m\n"+"-"*50)
print(f'Output directory: {outdir}')
print(f'Samples processed: {list_processed}')
print(f'Number of jobs : {njobs}')
print(f'Number of files : {nfiles}')
print("-"*50+"\n\n\033[0m")

