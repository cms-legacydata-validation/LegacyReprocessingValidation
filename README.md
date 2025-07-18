# REANA example - CMS Reconstruction (Legacy Reprocessing Validation)

[![image](https://img.shields.io/badge/discourse-forum-blue.svg)](https://forum.reana.io)
[![image](https://img.shields.io/github/license/reanahub/reana.svg)](https://github.com/cms-legacydata-validation/LegacyReprocessingValidation/blob/master/LICENSE)

## About

This REANA reproducible analysis example demonstrates the reconstruction procedure of the
CMS collaboration from
[raw data](http://opendata.cern.ch/search?page=1&size=20&experiment=CMS&file_type=raw) to
[Analysis Object Data (AOD)](https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookDataFormats#AoD),
for the year `2011` and the data set `DoubleElectron`.

The workflow consists of the steps need for the samples reconstruction, as taken from the
[CMS legacy validation repo](https://github.com/cms-legacydata-validation/RAWToAODValidation/tree/master).

## Reconstruction procedure

### 1 & 2. Input data and Analysis code

Any raw input data from the
[CERN open data platform](http://opendata.cern.ch/search?page=1&size=20&experiment=CMS&type=Dataset&subtype=Collision&subtype=Derived&subtype=Simulated&file_type=raw)
should be valid for reconstruction. In this example, the input is taken from:
`root://eospublic.cern.ch//eos/opendata/cms/Run2011A/DoubleElectron/RAW/v1/000/160/433/C046161E-0D4E-E011-BCBA-0030487CD906.root`

The reconstruction step can be repeated with a configuration file that depends on the
analyzed data, e.g. [this example](http://opendata.cern.ch/record/43), or by creating our
own configuration file (created in a CMS VM) and then changing the script accordingly:

```console
cmsDriver.py reco -s RAW2DIGI,L1Reco,RECO,USER:EventFilter/HcalRawToDigi/hcallaserhbhehffilter2012_cff.hcallLaser2012Filter --data --conditions FT_R_53_LV5::All --eventcontent AOD --customise Configuration/DataProcessing/RecoTLR.customisePrompt --no_exec --python reco_cmsdriver2011.py
```

### 3. Compute environment

In order to be able to rerun the analysis even several years in the future, we need to
"encapsulate the current compute environment", for example to freeze the software package
versions our analysis is using. We shall achieve this by preparing a
[Docker](https://www.docker.com/) container image for our analysis steps.

This analysis example runs within the [CMSSW](http://cms-sw.github.io/) analysis
framework that was packaged for Docker in
[cmsopendata](https://hub.docker.com/u/cmsopendata). The different images corresponds to
data sets taken in different years. Instructions can be found under
[this repo](http://opendata.cern.ch/docs/cms-guide-docker).

Moreover, the re-reconstruction task needs access run-time to the condition database and
inside a
[CMS VM](http://opendata.cern.ch/search?page=1&size=20&q=virtual%20machine&subtype=VM&type=Environment&experiment=CMS),
this is achieved with the commands:

```console
$ ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT_53_LV5_AN1_RUNA FT_53_LV5_AN1
$ ln -sf /cvmfs/cms-opendata-conddb.cern.ch/FT_53_LV5_AN1_RUNA.db FT_53_LV5_AN1_RUNA.db
```

For REANA, the condition database on CVMFS is automatically mounted via the workflow
configuration. The generated `reana.yaml` includes the necessary CVMFS resources:

```yaml
workflow:
  resources:
    cvmfs:
      - cms-opendata-conddb.cern.ch
```

This provides automatic access to the CMS conditions database without manual setup.

### 4. Analysis workflow

The workflow automatically sets up the CMS environment and handles:

1. **Environment Setup**: Configures CMSSW framework
2. **CVMFS Access**: Mounts CMS conditions database via CVMFS
3. **Dynamic Configuration**: Uses appropriate CMSSW version and global tags
4. **Reconstruction**: Runs RAW2DIGI → L1Reco → RECO → USER steps
5. **Analysis**: Generates physics object histograms

**Key Features:**
- **CVMFS Integration**: Automatic access to CMS conditions database
- **Dynamic Container Selection**: Uses appropriate CMSSW version containers
- **Automatic Configuration**: Downloads metadata from CMS Open Data Portal
- **Flexible File Selection**: Choose specific files or random samples

**Generated Outputs:**
- `reco_RAW2DIGI_L1Reco_RECO_USER.root`: Reconstructed AOD file
- `histodemo.root`: Physics object validation histograms

This demo represents a "workflow factory" script that will produce REANA workflows for
given parameters for the CMS RAW to AOD reconstruction procedure.

This enhanced version includes:
- **Automatic configuration** from CMS Open Data records via `--recid` parameter
- **Dynamic container selection** based on CMSSW version
- **CVMFS integration** for conditions database access
- **Simplified CLI interface** aligned with the base reana-demo-cms-reco

Following successful tests, we know that REANA is able to run CMS
reconstruction for a variety of RAW samples (e.g. dataset SingleMu) and data-taking years
(e.g. 2010, 2011, 2012).

### Example

Before running example, you might want to install necessary packages:

```console
$ # create new virtual environment
$ virtualenv ~/.virtualenvs/myreana
$ source ~/.virtualenvs/myreana/bin/activate
$ # install reana-commons and reana-client
$ pip install git+https://github.com/cms-legacydata-validation/LegacyReprocessingValidation.git@master#egg=cms-reco
$ # clone the repository for development
$ git clone https://github.com/cms-legacydata-validation/LegacyReprocessingValidation.git
$ cd LegacyReprocessingValidation
```

## Usage

### Basic Usage

Create a workflow using the default configuration:

```console
$ cms-reco create-workflow --directory my-workflow
    Created `my-workflow` directory.
$ cd my-workflow
$ reana-client run
```

### Advanced Usage with CMS Open Data Records

Generate a workflow from a specific CMS Open Data record:

```console
$ cms-reco create-workflow --recid 46 --directory workflow-2011-doubleelectron
    Created `workflow-2011-doubleelectron` directory.
$ cd workflow-2011-doubleelectron
$ reana-client run
```

### CLI Parameters

The `cms-reco create-workflow` command supports the following options:

- `--recid TEXT`: CMS Open Data record ID for automatic configuration
- `--directory TEXT`: Directory name for the generated workflow
- `--nevents TEXT`: Number of events to process (default: 1)
- `--files [first|smallest|largest|random|all]`: File selection method
- `--year [2010|2011|2012]`: Data-taking year
- `--workflow_engine [serial|cwl|yadage]`: Workflow engine to use
- `--compute_backend [kubernetes|htcondorcern]`: Compute backend
- `--config_file TEXT`: Configuration file path
- `--dataset TEXT`: Dataset name (default: DoubleElectron)
- `--quiet`: Suppress diagnostic output

### Examples

**Process 10 events from a specific record:**
```console
$ cms-reco create-workflow --recid 46 --nevents 10 --directory test-10-events
```

**Create CWL workflow:**
```console
$ cms-reco create-workflow --workflow_engine cwl --directory test-cwl
```

**Use smallest file from dataset:**
```console
$ cms-reco create-workflow --files smallest --directory test-smallest
```
