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
#fileList = cms.untracked.vstring('/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/789B3396-5DE0-E211-B22A-20CF3027A5AE.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/42AF32A7-5BE0-E211-8232-20CF305616F0.root')

fileList = cms.untracked.vstring('/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/789B3396-5DE0-E211-B22A-20CF3027A5AE.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/02C206F2-5FE0-E211-9F26-00259073E3C0.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/04462D77-60E0-E211-918A-20CF3027A5E2.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/04AC7692-59E0-E211-A800-90E6BA0D09B4.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/06F1C3EE-59E0-E211-B552-20CF305B0584.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/0E5EE58C-66E0-E211-94BF-00259073E438.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/16FFA656-5FE0-E211-837B-485B39800C36.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/1A0D6803-5DE0-E211-95B5-20CF30561712.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/1EC97B97-36E0-E211-BDCD-00259073E34C.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/203CFC97-4AE0-E211-B912-20CF305B057E.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/2062EC05-6CE0-E211-A50D-20CF305B0594.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/2689EDCF-55E0-E211-8AD6-90E6BA0D0990.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/2EC906B8-7AE0-E211-9998-00259073E37C.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/30A6F9E4-62E0-E211-90CB-485B39800B9D.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/382CB993-57E0-E211-A970-001EC9D7FF3B.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/403673BA-5AE0-E211-9897-00259073E452.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/42AF32A7-5BE0-E211-8232-20CF305616F0.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/44438139-62E0-E211-B08D-20CF3027A577.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/4639AA86-62E0-E211-B35D-E0CB4E1A1189.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/4AFA58B9-5CE0-E211-88F5-20CF30561712.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/4CAF9FE1-68E0-E211-BB33-20CF305B0590.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/58C1BD55-59E0-E211-A9F8-00259073E4BE.root','/store/mc/Summer13dr53X/DYToEE_M_20_TuneZ2star_13TeV-pythia6/GEN-SIM-RAW/PU25bx25_START53_V19D-v1/20000/60DB069F-54E0-E211-AD68-20CF305616E0.root')


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
