#!/usr/bin/env cwl-runner

# Note that if you are working on the analysis development locally, i.e. outside
# of the REANA platform, you can proceed as follows:
#
#   $ mkdir cwl-local-run
#   $ cd cwl-local-run
#   $ cp -a ../workflow/input.yml .
#   $ cp -a ../BuildFile.xml ../demoanalyzer_cfg.py .
#   $ mkdir src
#   $ cp -a ../src/PhysicsObjectsHistos.cc ./src/
#   $ cwltool --quiet --outdir="../results" ../workflow/workflow.cwl input.yml


cwlVersion: v1.0
class: Workflow

inputs:
  library:
    type: File
  build_file:
    type: File
  validation_script:
    type: File

outputs:
  result.root:
    type: File
    outputSource:
      reco/result.root
  histo.root:
    type: File
    outputSource:
      reco/histo.root
  reco.log:
    type: File
    outputSource:
      reco/reco.log


steps:
  reco:
    in:
      library: library
      build_file: build_file
      validation_script: validation_script
    run: reco.cwl
    out: [result.root, histo.root, reco.log]
