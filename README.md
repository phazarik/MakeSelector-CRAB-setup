# CRAB submission for MakeSelector based setup

This repository contains MakeSelector-based analysis codes that can be run on CRAB for large datasets. These are designed to work with Run3 samples. Currently optimized for Run3Summer22 (NanoAODv12), using `CMSSW_14_1_0_pre4` and an `el8_amd64_gcc12` architecture. These settings are compatible with lxplus8.

## Description of the setup

| **Category**  | **File/Directory**      | **Description** |
|---------------|-------------------------|-----------------|
|Source Codes   | `Skimmer`               | Contains the MakeSelector class.|
|               | `Setup`               | Contains additional headers needed by the skimmer.|
|               | `includeHeaders.h`      | Connects the additional headers to the skimmer.|
|               | `compile_and_run.C`     | ROOT macro for compiling and running the setup.|
|CRAB Submission| `FrameworkJobReport.xml`| XML report generated by CRAB submission.|
|               | `PSet.py`               | Manages the input file for CRAB jobs.|
|               | `crab_config.py`        | Main CRAB job configuration.|
|               | `crab_script.sh`        | Shell script that runs `shell_instructions.sh` in the job nodes.|
|               | `shell_instructions.sh` | This runs the ROOT macro for the skimmer in the job nodes.|
|Job Monitoring | `bulkSubmitCrab.py`     | Submit jobs for multiple DAS samples at once.|
|               | `checkStatus.py`        | Check status of all the submitted jobs.|
|               | `killAllJobs.py`        | Kill all the ongoing jobs.|

## How to run
Make sure the MakeSelector-based setup works locally by compiling and running it in the ROOT prompt. For this, a local nanoAOD (v12) file is needed.
```
[].L AnaScript.C+
[].x run_locally.C
```
Try out the `compile_and_run.C` directly.
```
[].x compile_and_run.C
```
Check if it can be done from bash by running the shell script, which takes input from `PSet.py`. This pulls an input file from DAS, so make sure to have the CMS-voms-proxy beforehand.
```
>> bash shell_instructions.sh Run3Summer23 samplename flag
```
If the shell instruction runs and produces an output file locally, try out a CRAB job as a dryrun.
```
export CRAB_CAMPAIGN=<campaign name> #Example: Run3Summer22
export CRAB_SAMPLENAME= <samplename> #Example:DYTo2L-4Jets_MLL-50
export CRAB_FLAG=<flag> #Example dy, or singlemuon
crab submit --dryrun crab_config.py General.requestName=<jobname> Data.inputDataset=<full DAS string>
```
### Submit jobs in bulk
Put the required sample information in `bulkSubmitCrab.py` and run it using Python3. 

## Important things to note
- Use relative paths. Absolute paths will not be recognized in the CRAB nodes.
- Use consistent CPU architecture and CMSSW environment.
- The `shell_instructions.sh` file redirects the input path `/store/mc/..root` to` root://cmsxrootd.fnal.gov///store/mc/..root`
- Organize the source code in the CRAB nodes exactly as it is. Look at `crab_script.sh` to see how it is done.
- Make sure that the following files have the correct path to the Skimmer (or any other MakeSelector-based setup).
-- `crab_script.sh` 
-- `compile_and_run.C`
- Make sure that the output file mentioned in `crab_config.py` and `shell_instructions.sh` have the exact name. Otherwise, CRAB won't be able to find this file in the work node and bring it to the dump area.

---
### Relevant links/tools
-   Sample database:  [Google spreadsheet](https://docs.google.com/spreadsheets/d/10LLDj0NRvGVtQPhoFLRR2A7NRblJRvnX_U7wvfeYhvw/edit?pli=1&gid=0#gid=0)
-   Bringing nanoAOD files from DAS to T2 area:  [phazarik/crabSkimSetup](https://github.com/phazarik/crabSkimSetup)
-   Simpler analysis template for nanoAOD files:  [phazarik/nanoAOD_analyzer](https://github.com/phazarik/nanoAOD_analyzer)
---
Written by [Prachurjya Hazarika](https://github.com/phazarik) and [Arnab Laha](https://github.com/alaha999)