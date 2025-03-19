import FWCore.ParameterSet.Config as cms

process = cms.Process("NANO")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.source = cms.Source("PoolSource", fileNames=cms.untracked.vstring())

process.source.fileNames = [
    #"root://cms-xrd-global.cern.ch///store/mc/Run3Summer22NanoAODv12/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/2520000/1571fd27-7879-4b8b-b0ed-6230a672d950.root"
    #"root://cmsxrootd.fnal.gov///store/mc/Run3Summer22NanoAODv12/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/40000/617c05b0-509b-4959-9952-0374ee640d58.root"
    #"root://cms-xrd-global.cern.ch///store/mc/Run3Summer22NanoAODv12/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/40000/617c05b0-509b-4959-9952-0374ee640d58.root"
    "/store/mc/Run3Summer22NanoAODv12/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/40000/617c05b0-509b-4959-9952-0374ee640d58.root"
    #DAS: /DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM
]
