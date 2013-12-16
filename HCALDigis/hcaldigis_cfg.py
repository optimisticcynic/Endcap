import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# User Flags

# set true for hcal local run data
hcalLocal = False

# set true to save reconstructed digis
outputRecoDigies = False

# set true to get direct digi outpur
printDigis = False

# input file list
fileList = cms.untracked.vstring('/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/789B3396-5DE0-E211-B22A-20CF3027A5AE.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/42AF32A7-5BE0-E211-8232-20CF305616F0.root')

if hcalLocal:
    process.source = cms.Source("HcalTBSource",
                                fileNames = fileList
                                )
else:
    process.source = cms.Source("PoolSource",
                                fileNames = fileList
                                )

process.TFileService = cms.Service("TFileService",
                                          fileName = cms.string("digis.root"),
                                   )

process.output = cms.OutputModule("PoolOutputModule",
                                  splitLevel = cms.untracked.int32(0),
                                  eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
                                  outputCommands = process.FEVTEventContent.outputCommands,
                                  fileName = cms.untracked.string('test_RAW2DIGI.root'),
                                  dataset = cms.untracked.PSet(
                                  filterName = cms.untracked.string(''),
                                  dataTier = cms.untracked.string('')
                )
     )

process.GlobalTag.globaltag = 'START53_V27::All'

process.load('EventFilter.HcalRawToDigi.HcalRawToDigi_cfi')
if not hcalLocal:
    process.hcalDigis.InputLabel = cms.InputTag('rawDataCollector')
    
process.demo = cms.EDAnalyzer('HCALDigis',
                              printDigi = cms.untracked.bool(printDigis))

process.p = cms.Path(process.hcalDigis * process.demo)
if outputRecoDigies:
    process.output_step = cms.EndPath(process.output)
