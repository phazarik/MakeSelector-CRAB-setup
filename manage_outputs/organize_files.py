import os, sys

basedir = "/eos/user/p/phazarik"
jobdir  = "Run3Summer22_skim_Rare"
dumpdir = "skimmed_2LSS_Run3Summer22" 
dryrun  = True
test    = False

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

    ### SingleTop
    ("ST_TBbartoLplusNuBbar", "/TBbartoLplusNuBbar-s-channel-4FS_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TbarBtoLminusNuB",   "/TbarBtoLminusNuB-s-channel-4FS_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TBbarQ",             "/TBbarQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TQbarto2Q",          "/TQbarto2Q-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TQbartoLNu",         "/TQbartoLNu-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TbarBQ",             "/TbarBQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TbarQto2Q",          "/TbarQto2Q-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    ("ST_TbarQtoLNu",         "/TbarQtoLNu-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),

    ### TW
    ("TW_TWminusto2L2Nu",   "/TWminusto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    ("TW_TWminustoLNu2Q",   "/TWminustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    ("TW_TbarWplusto2L2Nu", "/TbarWplusto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    ("TW_TbarWplustoLNu2Q", "/TbarWplustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    
    ### Rare
    ("RareTop_THQ", "/THQ_ctcvcp_HIncl_M-125_4FS_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_THW", "/THW_ctcvcp_HIncl_M-125_5FS_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTHHto2B", "/TTH_Hto2B_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v3/NANOAODSIM", "rare"),
    ("RareTop_TTHHto2Mu", "/TTH_Hto2Mu_M-125_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v3/NANOAODSIM", "rare"),
    ("RareTop_TTHHto2Z", "/TTH_Hto2Z_4LFilter_M-125_TuneCP5_13p6TeV_powheg-jhugenv752-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTTT", "/TTTT_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTWH", "/TTWH_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTWW", "/TTWW_TuneCP5_13p6TeV_madgraph-madspin-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTZH", "/TTZH_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTZZ", "/TTZZ_TuneCP5_13p6TeV_madgraph-madspin-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TZQB", "/TZQB-Zto2L-4FS_MLL-30_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "rare"),
    ("RareTop_TTWZ", "/TTWZ_TuneCP5_13p6TeV_madgraph-pythia8/Run3Summer22NanoAODv11-126X_mcRun3_2022_realistic_v2-v2/NANOAODSIM", "rare")

]


for fullsamplename, fulldasname, tag in samples:

    print(f'\033[033m\nProcessing {fullsamplename}\033[0m')
    sample    = fullsamplename.split('_')[0]
    subsample = fullsamplename.split('_')[1]
    dump = os.path.join(basedir, dumpdir, sample, subsample)
    if not dryrun: os.makedirs(dump, exist_ok=True)

    dasname = fulldasname.split('/')[1]
    searchdir = os.path.join(basedir, jobdir, dasname)
    if not os.path.exists(searchdir):
        print(f'\033[31mPath does not exists: {searchdir}. Skipping.\033[0m')
        continue
    
    print('Searching files in: '+searchdir)

    files_found = False
    for rootdir, _, files in os.walk(searchdir):
        root_files = [f for f in files if f.endswith('.root')]
        if root_files:
            print(f'Found {len(root_files)} root files in: {rootdir}')
            files_found = True
            nfile = 0
            for file in root_files:
                src = os.path.join(rootdir, file)
                dst = os.path.join(dump,    file)
                if not dryrun: os.system(f'cp "{src}" "{dst}"')
                #if os.path.exists(dst): print(f'\033[31mWarning: {dst} already exists. Skipping copy.\033[0m')
                #else:
                if not dryrun:
                    os.system(f'cp "{src}" "{dst}"')
                    nfile += 1
                
            print('Destination: '+dump)
            print(f'Copied {nfile} files.')

    if not files_found: print(f'\033[31mNo root files in: {searchdir}, skipping.\033[0m')
    if test: break ##sample

print(f'\nAll files in {jobdir} copied to {dumpdir}.\n')
