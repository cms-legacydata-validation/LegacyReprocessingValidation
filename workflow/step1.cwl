class: CommandLineTool
cwlVersion: v1.0

requirements:
  - class: DockerRequirement
    dockerPull: docker.io/cmsopendata/cmssw_5_3_32

baseCommand:
  - /bin/zsh

inputs:
  - id: reco_tool
    type: File

arguments:
  - position: 0
    prefix: '-c'
    valueFrom: |
      source /opt/cms/cmsset_default.sh ;\
      scramv1 project CMSSW CMSSW_5_3_32 ;\
      cd CMSSW_5_3_32/src ;\
      eval `scramv1 runtime -sh` ;\
      ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT_53_LV5_AN1_RUNA FT_53_LV5_AN1 ;\
      ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT_53_LV5_AN1_RUNA.db FT_53_LV5_AN1_RUNA.db ;\
      ls -l ;\
      ls -l /cvmfs/ ;\
      scp ../../../../$(inputs.reco_tool.basename) . ;\
      cmsRun $(inputs.reco_tool.basename)

outputs:
  - id: result.root
    type: File
    outputBinding:
      glob: CMSSW_5_3_32/src/reco_RAW2DIGI_L1Reco_RECO_USER.root
  - id: step1.log
    type: stdout

stdout: step1.log
