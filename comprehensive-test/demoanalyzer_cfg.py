#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""CMS validation script."""

import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = 'INFO'
process.MessageLogger.categories.append('Demo')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit=cms.untracked.int32(1)
)
process.options = cms.untracked.PSet(
    wantSummary=cms.untracked.bool(True),
    SkipEvent=cms.untracked.vstring('ProductNotFound')
)

process.maxEvents = cms.untracked.PSet(input=cms.untracked.int32(20000))

process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames=cms.untracked.vstring(
        'file:reco_RAW2DIGI_L1Reco_RECO_USER.root'),
    lumisToProcess=cms.untracked.VLuminosityBlockRange('160957:1-160957:max')
    # firstRun = cms.untracked.uint32(169957),
    # firstEvent = cms.untracked.uint32(488034889)
)

process.demo = cms.EDAnalyzer(
    'PhysicsObjectsHistos',
    minTracks=cms.untracked.uint32(0)
)

process.TFileService = cms.Service(
    "TFileService",
    fileName=cms.string('histodemo.root')
)


process.p = cms.Path(process.demo)
