class: CommandLineTool
cwlVersion: v1.0

requirements:
  - class: DockerRequirement
    dockerPull: docker.io/cmsopendata/cmssw_{{cookiecutter.cmssw_version}}

baseCommand:
  - /bin/zsh

inputs:
  library: File
  build_file: File
  validation_script: File

arguments:
  - position: 0
    prefix: '-c'
    valueFrom: |
      source /opt/cms/cmsset_default.sh
      scramv1 project CMSSW CMSSW_{{cookiecutter.cmssw_version}}
      cd CMSSW_{{cookiecutter.cmssw_version}}/src
      eval `scramv1 runtime -sh`
      mkdir Reconstruction && cd Reconstruction
      mkdir Validation && cd Validation
      cmsDriver.py reco -s RAW2DIGI,L1Reco,RECO,USER:EventFilter/HcalRawToDigi/hcallaserhbhehffilter2012_cff.hcallLaser2012Filter --data --filein='{{cookiecutter.dataset_file}}' --conditions {{cookiecutter.global_tag}}::All --eventcontent AOD  --no_exec --python reco_cmsdriver.py
      sed -i 's/from Configuration.AlCa.GlobalTag import GlobalTag/process.GlobalTag.connect = cms.string("sqlite_file:\/cvmfs\/cms-opendata-conddb.cern.ch\/{{cookiecutter.global_tag}}{{cookiecutter.global_tag_suffix}}.db")/g' reco_cmsdriver.py
      sed -i 's/# Other statements/from Configuration.AlCa.GlobalTag import GlobalTag/g' reco_cmsdriver.py
      sed -i "s/process.GlobalTag = GlobalTag(process.GlobalTag, '{{cookiecutter.global_tag}}::All', '')/process.GlobalTag.globaltag = '{{cookiecutter.global_tag}}::All'/g" reco_cmsdriver.py
      ln -sf /cvmfs/cms-opendata-conddb.cern.ch/{{cookiecutter.global_tag}}{{cookiecutter.global_tag_suffix}} {{cookiecutter.global_tag}}
      ln -sf /cvmfs/cms-opendata-conddb.cern.ch/{{cookiecutter.global_tag}}{{cookiecutter.global_tag_suffix}}.db {{cookiecutter.global_tag}}{{cookiecutter.global_tag_suffix}}.db
      ls -l
      ls -l /cvmfs/
      cmsRun reco_cmsdriver.py
      mkdir src
      scp ../../../../../../src/$(inputs.library.basename) ./src
      scp ../../../../../../$(inputs.build_file.basename) .
      scp ../../../../../../$(inputs.validation_script.basename) .
      scram b
      cmsRun $(inputs.validation_script.basename)

outputs:
  - id: result.root
    type: File
    outputBinding:
      glob: CMSSW_{{cookiecutter.cmssw_version}}/src/Reconstruction/Validation/reco_RAW2DIGI_L1Reco_RECO_USER.root
  - id: histo.root
    type: File
    outputBinding:
      glob: CMSSW_{{cookiecutter.cmssw_version}}/src/Reconstruction/Validation/histodemo.root
  - id: reco.log
    type: stdout

stdout: reco.log
