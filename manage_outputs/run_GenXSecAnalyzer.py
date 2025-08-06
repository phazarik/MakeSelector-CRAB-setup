#!/usr/bin/env python3
# =============================================================================
# Script: run_GenXAnalyzer.py
#
# Description:
#   This script calculates MC cross-sections using CMS's GenXsecAnalyzer
#   from a list of datasets. It queries DAS to find the MiniAOD parent,
#   fetches a representative file, and runs cmsRun to extract the cross-section.
#
# Requirements:
#   - Valid CMS environment (CMSSW set up and active)
#   - Valid VOMS proxy (run: voms-proxy-init -voms cms)
#   - File: genXsec_cfg.py (auto-downloaded if missing)
#   - Input file: a Python-formatted list of datasets, e.g. samplelists/2018_UL.txt
#     Format: (("tag", "dataset_path", "category"), ... )
#     Only entries with category *not in* {"muon", "egamma"} will be processed.
#
# Usage:
#   inside CMSSW_X_X_X/src:
#   - do cmsenv, create voms-proxy
#   - source the ../samplelists/{campaign}.txt file in this script.
#   python3 run_GenXAnalyzer.py
#
# Output:
#   - Displays cross-section table as datasets are processed
#   - Failing cases are printed in red with debug info
#   - Elapsed time printed at the end
#
# Notes:
#   - The script gracefully handles missing parents, files, or xsec info.
#   - Only the first MINIAOD parent is used if multiple are found.
#   - Works with official global XRootD endpoint (root://cms-xrd-global.cern.ch)
# =============================================================================

import os
import subprocess
import ast
import time
from datetime import timedelta

RED = "\033[31m"
RESET = "\033[0m"

def run_command(cmd):
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return (result.stdout + result.stderr).strip()

def extract_xsec(output):
    for line in output.split("\n"):
        if "After matching: total cross section" in line:
            parts = line.split("=")
            if len(parts) > 1: return parts[1].strip()
    for line in output.split("\n"):
        if "After filter: final cross section" in line:
            parts = line.split("=")
            if len(parts) > 1: return parts[1].strip()
    return "Not found"

def color_if_failed(xsec):
    if xsec in ["No parent", "No file", "Not found"]:
        return f"{RED}{xsec}{RESET}"
    return xsec

def process_dataset(name, dataset):
    parent_cmd = f'dasgoclient --query="parent dataset={dataset}"'
    parent_output = run_command(parent_cmd)
    parent_lines = parent_output.splitlines()
    parent_dataset = next((line for line in parent_lines if "MINIAOD" in line), "")
    if not parent_dataset:
        print(f"{RED}[DEBUG] No valid MINIAOD parent found for: {name}{RESET}")
        print(f"{RED}[DEBUG] Parent list:\n{parent_output}{RESET}")
        print(f"{RED}[DEBUG] Command: {parent_cmd}{RESET}")
        return name, "No parent"

    file_cmd = f'dasgoclient --query="file dataset={parent_dataset}" | head -n 1'
    miniAOD_file = run_command(file_cmd)
    if not miniAOD_file:
        print(f"{RED}[DEBUG] No file found for: {name}{RESET}")
        print(f"{RED}[DEBUG] Parent dataset: {parent_dataset}{RESET}")
        print(f"{RED}[DEBUG] Command: {file_cmd}{RESET}")
        return name, "No file"

    cmsRun_cmd = f"cmsRun genXsec_cfg.py inputFiles=file:root://cms-xrd-global.cern.ch//{miniAOD_file}"
    output = run_command(cmsRun_cmd)
    xsec = extract_xsec(output)

    if xsec == "Not found":
        print(f"{RED}[DEBUG] No cross-section found for: {name}{RESET}")
        print(f"{RED}[DEBUG] cmsRun command: {cmsRun_cmd}{RESET}")
        print(f"{RED}[DEBUG] Output:\n{output}{RESET}")

    return name, xsec

def check_env():
    if not os.environ.get("CMSSW_BASE"):
        print("CMSSW environment not set. Run 'cmsenv' inside a CMSSW release.")
        return False
    result = subprocess.run("voms-proxy-info --timeleft", shell=True, capture_output=True, text=True)
    if result.returncode != 0:
        print("Failed to check VOMS proxy. Is 'voms-proxy-info' available?")
        return False
    timeleft = result.stdout.strip()
    if not timeleft.isdigit() or int(timeleft) <= 0:
        print("No valid VOMS proxy found. Run 'voms-proxy-init -voms cms'.")
        return False
    return True

def main():
    if not check_env(): return
    if not os.path.exists("genXsec_cfg.py"):
        os.system("curl -s https://raw.githubusercontent.com/cms-sw/genproductions/master/Utilities/calculateXSectionAndFilterEfficiency/genXsec_cfg.py -o genXsec_cfg.py")

    with open("../samplelists/2018_UL.txt") as f:
        entries = ast.literal_eval(f.read())

    mc_entries = [(name, path) for name, path, tag in entries if tag not in ["muon", "egamma"]]
    print(f"running on {len(mc_entries)} samples ...\n")

    name_width = max(len(name) for name, _ in mc_entries) + 2
    print("samplename".ljust(name_width) + "cross-section")
    print("-" * (name_width + 25))

    start = time.time()
    results = {}
    for name, path in mc_entries:
        #exceptions:
        if "QCD" not in name: continue

        name, xsec = process_dataset(name, path)
        results[name] = xsec
        print(name.ljust(name_width) + color_if_failed(xsec))

    elapsed = timedelta(seconds=int(time.time() - start))
    print(f"\nTotal time: {elapsed}")

if __name__ == "__main__": main()
