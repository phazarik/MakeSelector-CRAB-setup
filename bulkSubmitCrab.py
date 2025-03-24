#----------------------------------------------
# Submitting crab jobs in bulk.
#
# Note: Manage the parameters that are fed
# into crab_config.py according to your need.
#---------------------------------------------

import os,sys

campaign = "Run3Summer22"
test   = False
dryrun = False

### Note: For data, use flag == 'singlemuon' or 'egamma'

samples=[
    ### Data:
    #("Muon_C",   "/Muon/Run2022C-ReRecoNanoAODv11-v1/NANOAOD",   "muon"),
    #("Muon_D",   "/Muon/Run2022D-ReRecoNanoAODv11-v1/NANOAOD",   "muon"),
    #("EGamma_C", "/EGamma/Run2022C-ReRecoNanoAODv11-v1/NANOAOD", "egamma"),
    #("EGamma_D", "/EGamma/Run2022D-ReRecoNanoAODv11-v1/NANOAOD", "egamma"),
    
    ### SingleV:
    #("WtoLNu_Inclusive",  "/WtoLNu-2Jets_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "w"),
    #("WGtoLNuG_10to100",  "/WGtoLNuG-1Jets_PTG-10to100_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "wgamma"),
    #("WGtoLNuG_100to200", "/WGtoLNuG-1Jets_PTG-100to200_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "wgamma"),
    #("WGtoLNuG_200to400", "/WGtoLNuG-1Jets_PTG-200to400_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v1/NANOAODSIM", "wgamma"),
    #("WGtoLNuG_400to600", "/WGtoLNuG-1Jets_PTG-400to600_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v1/NANOAODSIM", "wgamma"),
    #("WGtoLNuG_600toInf", "/WGtoLNuG-1Jets_PTG-600_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v3/NANOAODSIM", "wgamma"),
    #("DYto2L_10to50",     "/DYto2L-4Jets_MLL-10to50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v1/NANOAODSIM", "dy"),
    #("DYto2L_50toInf",    "/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "dy"),
    #("ZGamma_ZGto2LG",    "/ZGto2LG-1Jets_ntgc_5f_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "zgamma"),

    ### TTbar:
    #("TT_TTto2L2Nu",    "/TTto2L2Nu-3Jets_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("TT_TTtoLminusNu", "/TTtoLminusNu2Q-3Jets_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("TT_TTtoLplusNu",  "/TTtoLplusNu2Q-3Jets_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),

    ### SingleTop
    #("ST_TBbartoLplusNuBbar", "/TBbartoLplusNuBbar-s-channel-4FS_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TbarBtoLminusNuB",   "/TbarBtoLminusNuB-s-channel-4FS_TuneCP5_13p6TeV_amcatnlo-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TBbarQ",             "/TBbarQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TQbarto2Q",          "/TQbarto2Q-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TQbartoLNu",         "/TQbartoLNu-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TbarBQ",             "/TbarBQ_t-channel_4FS_TuneCP5_13p6TeV_powheg-madspin-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TbarQto2Q",          "/TbarQto2Q-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),
    #("ST_TbarQtoLNu",         "/TbarQtoLNu-t-channel_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "ttbar"),

    ### TW
    ("TW_TWminusto2L2Nu",   "/TWminusto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    ("TW_TWminustoLNu2Q",   "/TWminustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    ("TW_TbarWplusto2L2Nu", "/TbarWplusto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),
    ("TW_TbarWplustoLNu2Q", "/TbarWplustoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM", "tw"),

]

jobname ="nanoSkim"
    
for samplename, dataset, flag in samples:
    requestname = jobname + '_' + samplename
    
    ### Setting up the arguments for crab_config:
    arg3 = 'General.requestName=' + requestname # Name of the sub-directory in the output area.
    arg4 = 'Data.inputDataset='   + dataset     # Input DAS string
    arg5 = campaign
    arg6 = samplename
    arg7 = flag

    ### Set ENV here
    os.environ['CRAB_CAMPAIGN'] = campaign
    os.environ['CRAB_SAMPLENAME'] = samplename
    os.environ['CRAB_FLAG'] = flag
    
    ### Main process line:
    processline = f'crab submit crab_config.py {arg3} {arg4}'

    print('-'*50)
    print(f'\nProcessing \033[33m{dataset}\033[0m')
    if dryrun :
        print('export CRAB_CAMPAIGN='+campaign)
        print('export CRAB_SAMPLENAME='+samplename)
        print('export CRAB_FLAG='+flag)
        print(processline)
    else: os.system(processline)

    if test: break

    # Working Example:
    # export CRAB_CAMPAIGN=Run3Summer22
    # export CRAB_SAMPLENAME=DYTo2L-4Jets_MLL-50
    # export CRAB_FLAG=dy
    # crab submit crab_config.py General.requestName=nanoSkim_DYTo2L-4Jets_MLL-50 Data.inputDataset=/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM 

print("\nDone!")
