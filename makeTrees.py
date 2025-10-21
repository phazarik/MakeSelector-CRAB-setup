import os, sys
import time
from datetime import timedelta
start_time = time.time()

import argparse
parser = argparse.ArgumentParser()
parser.add_argument('--dryrun', action='store_true', help='Check if everything is correct before submitting')
parser.add_argument('--test', action='store_true', help='Check one job')
args=parser.parse_args()

finalstate = "2LSS"
campaign = "Run3Summer22EE"
jobname = f"skimmed_2L_Run3Summer22EE_2025-10-19"
outdir  = f"EGamma/tree_{finalstate}_baseline_{campaign}"

outdir  = os.path.join("/eos/user/p/phazarik/TREEDUMP", outdir)
indir   = os.path.join("/eos/user/p/phazarik/SKIMDUMP", jobname)
samples = os.listdir(indir)
if not args.dryrun: os.makedirs(outdir, exist_ok=True)

hline = "-"*30
njobs, nfiles = 0, 0
nsample = 0
list_processed=[]

for sample in samples:
    if not os.path.isdir(os.path.join(indir, sample)): continue
    nsample += 1
    subsamples = os.listdir(os.path.join(indir, sample))

    if "EGamma" not in sample: continue
    #if sample not in ["VLLD-ele", "VLLD-mu", "VV", "VVSS", "VVV", "WGtoLNuG", "WtoLNu"]: continue
        
    print("\n"+hline)
    print(f"\033[93m({nsample}/{len(samples)}) Processing {sample}\033[0m")
    print(hline)

    flag = "mc"
    if 'Muon' in sample:    flag='muon'
    if 'EGamma' in sample:  flag='egamma'
    if sample == 'QCDMu' :  flag='qcd'
    if sample == 'QCDEle' : flag='qcd'
    if sample == 'DYto2L':  flag='dy'
    if sample == 'TT':      flag='ttbar'
    if 'VLLD' in sample:    flag='doublet'

    sample_time_start = time.time()

    nsubsample = 0
    for subsample in subsamples:
        if not os.path.isdir(os.path.join(indir, sample, subsample)): continue
        nsubsample += 1
        
        fullsamplename = f"{sample}_{subsample}"
        #if "1400" not in fullsamplename: continue
        #if "TT_TTtoLNu2Q" not in fullsamplename: continue
        print(f'\n\033[93m({nsample}/{len(samples)}) \033[94m({nsubsample}/{len(subsamples)}) Processing {fullsamplename} ... \033[0m')
        
        infiledir = os.path.join(indir, sample, subsample)
        nfiles += len(os.listdir(infiledir))
        infiles = os.path.join(infiledir, "*root")
        outfile = os.path.join(outdir, f"tree_{fullsamplename}.root")

        rootmacro = "TreeMaker/compile_and_run.C"
        arguments = f'"{infiles}", "{outfile}", "{campaign}", "{fullsamplename}", "{flag}"'
        command = f"root -q -b -l '{rootmacro}({arguments})'"

        print(f"\033[33m{command}\033[0m")
        if not args.dryrun: os.system(command)
        
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

print("\n"+"-"*50)
print(f'Output directory: \033[93m{outdir}\033[0m')
print(f'Samples processed: {list_processed}')
print(f'Number of jobs : {njobs}')
print(f'Number of files : {nfiles}')
print(f"Total time taken: {time_fmt}")
print("-"*50+"\n")

