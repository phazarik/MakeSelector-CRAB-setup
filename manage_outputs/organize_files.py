import os, sys

basedir = "/eos/user/p/phazarik"
jobdir  = "Run3Summer22_skim_singleV"
dumpdir = "skimmed_2LSS_Run3Summer22" 
dryrun = True
test   = False

samples=[
    ### SingleV:
    ("WtoLNu_Inclusive",  "/WtoLNu-2Jets_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "w"),
    ("WGtoLNuG_10to100",  "/WGtoLNuG-1Jets_PTG-10to100_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "wgamma"),
    ("WGtoLNuG_100to200", "/WGtoLNuG-1Jets_PTG-100to200_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "wgamma"),
    ("WGtoLNuG_200to400", "/WGtoLNuG-1Jets_PTG-200to400_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v1/NANOAODSIM", "wgamma"),
    ("WGtoLNuG_400to600", "/WGtoLNuG-1Jets_PTG-400to600_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v1/NANOAODSIM", "wgamma"),
    ("WGtoLNuG_600toInf", "/WGtoLNuG-1Jets_PTG-600_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v3/NANOAODSIM", "wgamma"),
    ("DYto2L_10to50",     "/DYto2L-4Jets_MLL-10to50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v1/NANOAODSIM", "dy"),
    ("DYto2L_50toInf",    "/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "dy"),
    ("ZGamma_ZGto2LG",    "/ZGto2LG-1Jets_ntgc_5f_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "zgamma"),

    ### TTbar:
    ("TT_TTto2L2Nu",    "/TTto2L2Nu-3Jets_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("TT_TTtoLminusNu", "/TTtoLminusNu2Q-3Jets_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("TT_TTtoLplusNu",  "/TTtoLplusNu2Q-3Jets_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
]

for fullsamplename, fulldasname, tag in samples:

    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')
    sample    = fullsamplename.split('_')[0]
    subsample = fullsamplename.split('_')[1]
    dump = os.path.join(basedir, dumpdir, sample, subsample)
    if not dryrun: os.makedirs(dump, exist_ok=True)

    dasname = fulldasname.split('/')[1]
    searchdir = os.path.join(basedir, jobdir, dasname)
    print('Searching files in: '+searchdir)
    
    for rootdir, _, files in os.walk(searchdir):
        root_files = [f for f in files if f.endswith('.root')]
        if root_files:
            print(f'Found {len(root_files)} root files in: {rootdir}')
            nfile = 0
            for file in root_files:
                src = os.path.join(rootdir, file)
                dst = os.path.join(dump,    file)
                if not dryrun: os.system(f'cp "{src}" "{dst}"')
                if os.path.exists(dst): print(f'\033[91mWarning: {dst} already exists. Skipping copy.\033[0m')
                else:
                    if not dryrun:
                        os.system(f'cp "{src}" "{dst}"')
                        nfile += 1
                
            print('Destination: '+dump)
            print(f'Copied {nfile} files.')

    if test: break ##sample

print(f'\nAll files in {jobdir} copied to {dumpdir}.\n')
