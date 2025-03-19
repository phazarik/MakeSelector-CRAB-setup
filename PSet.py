import FWCore.ParameterSet.Config as cms

process = cms.Process("NANO")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))

process.source = cms.Source("PoolSource", fileNames=cms.untracked.vstring())

process.source.fileNames = [
    "/store/mc/Run3Summer22NanoAODv12/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/40000/617c05b0-509b-4959-9952-0374ee640d58.root"
    #DAS: /DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM
]
