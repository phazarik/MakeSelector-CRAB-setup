import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing

# Set up VarParsing to allow argument passing from crab_config.py
options = VarParsing.VarParsing('analysis')
options.register('campaign', 'Run3Summer22', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Campaign name")
options.register('flag', 'dy', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Flag")
options.register('samplename', 'DYto2L-4Jets_MLL-50', VarParsing.VarParsing.multiplicity.singleton, VarParsing.VarParsing.varType.string, "Sample name")
options.parseArguments()

process = cms.Process("NANO")
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(10))
process.source = cms.Source("PoolSource", fileNames=cms.untracked.vstring())
process.source.fileNames = [
    "/store/mc/Run3Summer22NanoAODv12/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/2520000/1571fd27-7879-4b8b-b0ed-6230a672d950.root"
    #DAS: /DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/Run3Summer22NanoAODv12-130X_mcRun3_2022_realistic_v5-v2/NANOAODSIM
]

# Assign parameters from crab_config.py
process.custom_params = cms.PSet(
    campaign_   = cms.string(options.campaign),
    flag_       = cms.string(options.flag),
    samplename_ = cms.string(options.samplename)
)
