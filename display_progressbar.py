#!/usr/bin/env python3
# =============================================================================
# display_progressbar.py
#
# Purpose:
#   Scans all CRAB job directories inside the "submitted/" folder and
#   displays their statuses in a colorized table with a segmented ANSI
#   progress bar. The progress bar reflects CRAB status percentages:
#   Failed -> Finished -> Transferring -> Running -> Idle.
#
# Features:
#   - Looks only at subdirectories in "submitted/" (each expected to contain a CRAB task).
#   - Dynamic column width based on the longest job name.
#   - ANSI color coded segments and percentage columns:
#         Gray (Idle), Yellow (Running), Cyan (Transferring),
#         Blue (Finished), Red (Failed).
#   - Keeps alignment correct by padding after ANSI reset codes.
#   - Creates a JSON file (jobIDs.json) mapping CRAB folders to job IDs.
#   - Warns if CMSSW or a valid VOMS proxy is missing.
#
# Usage:
#   python3 display_progressbar.py
#
# Notes:
#   - Designed for lxplus / CRAB workflows at CERN.
#   - Requires that "crab status -d <folder>" works for each directory.
# =============================================================================

import os, subprocess, json, re
import time
from datetime import timedelta

RESET = "\033[0m"
RED = "\033[31m"
RED_BOLD = "\033[1;31m"
BLUE = "\033[34m"
BLUE_BOLD = "\033[1;34m"
YELLOW = "\033[33m"
YELLOW_BOLD = "\033[93m"

COLORS = {
    "idle": "\033[90m",
    "running": "\033[33m",
    "transferring": "\033[36m",
    "finished": "\033[34m",
    "failed": "\033[31m"
}

# ------------------------------------------------------------------------------------
def parse_crab_status_output(output):
    job_info = {
        "total": 0,
        "idle": 0, "running": 0, "transferring": 0,
        "finished": 0, "failed": 0,
        "unsubmitted": 0,
        "CRAB": "-", "Scheduler": "-"
    }
    percentages = {"idle": "0%", "running": "0%", "transferring": "0%", "finished": "0%", "failed": "0%"}

    for line in output.splitlines():

        if "Status on the CRAB server:" in line:
            crab_raw = line.split("Status on the CRAB server:")[-1].strip()
            if "on command" in crab_raw: crab_raw = crab_raw.split("on command")[0].strip()
            job_info["CRAB"] = crab_raw

        elif "Status on the scheduler:" in line:
            sched_raw = line.split("Status on the scheduler:")[-1].strip()
            if "on command" in sched_raw: sched_raw = sched_raw.split("on command")[0].strip()
            job_info["Scheduler"] = sched_raw

        m = re.search(r"(finished|transferring|running|idle|failed|toRetry|unsubmitted)\s+(\d+\.?\d*)%\s+\((\s*\d+)\s*/\s*(\d+)\)", line)
        if m:
            state, pct, count, total = m.groups()
            state = state.strip()
            count = int(count.strip())
            total = int(total.strip())

            if state == "unsubmitted":
                job_info["unsubmitted"] += count
            elif state == "toRetry":
                job_info["idle"] += count
            else:
                job_info[state] = count
                percentages[state] = f"{pct}%"

            job_info["total"] = total

    # Calculate submitted jobs (exclude unsubmitted)
    submitted_total = job_info["total"] - job_info["unsubmitted"]
    job_info["submitted_total"] = submitted_total

    # Recompute percentages relative to submitted jobs
    if submitted_total > 0:
        for key in ["idle", "running", "transferring", "finished", "failed"]:
            pct_val = int(job_info[key] / submitted_total * 100) if submitted_total else 0
            percentages[key] = f"{pct_val}%"
    else:
        for key in percentages: percentages[key] = "0%"

    job_info["percentages"] = percentages
    return job_info

# ------------------------------------------------------------------------------------
def make_progress_bar(pct, length=50):
    order = ["failed", "finished", "transferring", "running", "idle"]
    raw = [float(pct[s][:-1]) / 100 * length for s in order]
    raw[-1] += float(pct.get("unsubmitted", "0%")[:-1]) / 100 * length  # Add unsubmitted to idle

    # If all zero -> solid gray bar
    if sum(raw) == 0:
        return COLORS["idle"] + "#" * length + RESET

    segs = [[name, int(val)] for name, val in zip(order, raw)]
    total = sum(s[1] for s in segs)
    missing = length - total

    if missing > 0:
        remainders = sorted([(raw[i] - segs[i][1], i) for i in range(len(order)) if raw[i] > 0], reverse=True)
        for _, idx in remainders[:missing]:
            segs[idx][1] += 1

    bar = ""
    for name, count in segs:
        if count > 0:
            bar += COLORS[name] + "#" * count
    return bar + RESET

# ------------------------------------------------------------------------------------
def colorize_aligned(text, color, width):
    visible_len = len(text)
    return f"{color}{text}{RESET}" + " " * (width - visible_len)

def format_pct(pct):  return f"{pct:<8}"
def dash_if_zero(value, color, width):
    return f"{'-':<{width}}" if value == 0 else colorize_aligned(str(value), color, width)

def alphanum_key(s):
    return [int(t) if t.isdigit() else t for t in re.split("([0-9]+)", s)]

# ------------------------------------------------------------------------------------
def check_status_all_jobs():
    start_time = time.time()
    submitted_dir = "submitted"
    jobid_dict = {}
    failed_jobs = []
    completed_jobs = []
    bar_length = 50

    all_folders = [f for f in os.listdir(submitted_dir) if os.path.isdir(os.path.join(submitted_dir, f))]
    max_jobname_len = max((len(f) for f in all_folders), default=10) + 4
    print(f"Checking {len(all_folders)} jobs...")

    # Header
    print(f"\n{YELLOW_BOLD}{'No':<4} {'Job Name':<{max_jobname_len}} {'Progress':<{bar_length+2}} "
          f"{'CRAB':<14} {'Scheduler':<14} {'Total':<8} {'Unsub':<8} {'Idle':<8} {'Running':<8} "
          f"{'Transf':<8} {'Fin':<8} {'Failed':<10}{RESET}")

    count = 1
    for folder in sorted(all_folders, key=alphanum_key):
        folder_path = os.path.join(submitted_dir, folder)
        output = os.popen(f"crab status -d {folder_path}").read()
        job_info = parse_crab_status_output(output)
        if job_info["failed"] > 0: failed_jobs.append(folder_path)
        if job_info["Scheduler"] == "COMPLETED":
            #if not ("Muon" in folder_path or "EGamma" in folder_path):
            completed_jobs.append(folder_path)

        pct = job_info["percentages"]
        bar = make_progress_bar(pct, bar_length) + "  "

        job_id = "-"
        for line in output.splitlines():
            if line.startswith("Task name:"):
                job_id_full = line.split()[-1]
                job_id = job_id_full.split(":")[0]
                break

        ## Put entry in jobID
        sample_key = folder.replace("SingleElectron", "EGamma").replace("SingleMuon", "Muon")
        for prefix in ["EGamma", "Muon"]:
            if prefix in sample_key:
                idx = sample_key.index(prefix)
                sample_key = sample_key[idx:]
                jobid_dict[sample_key] = job_id
                break

        crab_status_raw = job_info["CRAB"]
        if crab_status_raw in ["SUBMITFAILED"]: crab_status = colorize_aligned(crab_status_raw, RED, 13)
        else: crab_status = f"{crab_status_raw:<13}"
        scheduler_status_raw = job_info["Scheduler"]
        if scheduler_status_raw == "COMPLETED": scheduler_status = colorize_aligned(scheduler_status_raw, BLUE, 13)
        elif scheduler_status_raw == "FAILED":  scheduler_status = colorize_aligned(scheduler_status_raw, RED,  13)
        else: scheduler_status = f"{scheduler_status_raw:<13}"

        idle_colored  = dash_if_zero(job_info['idle'], COLORS["idle"], 8)
        run_colored   = dash_if_zero(job_info['running'], COLORS["running"], 8)
        trans_colored = dash_if_zero(job_info['transferring'], COLORS["transferring"], 8)
        fin_colored   = dash_if_zero(job_info['finished'], COLORS["finished"], 8)
        fail_colored  = dash_if_zero(job_info['failed'], COLORS["failed"], 10)

        print(f"{count:<4} {folder:<{max_jobname_len}} {bar:<{bar_length+2}} "
              f"{crab_status}  {scheduler_status}  "
              f"{job_info['submitted_total']:<8} {job_info['unsubmitted']:<8} "
              f"{idle_colored} {run_colored} {trans_colored} {fin_colored} {fail_colored}")
        count += 1

    with open("jobIDs.json", "w") as f: json.dump(jobid_dict, f, indent=4)

    elapsed = time.time() - start_time

    # Resubmit failed jobs
    if failed_jobs:
        print(f"\n{RED}[INFO] Found failed jobs. Suggested resubmit commands:{RESET}")
        for job in failed_jobs: print(f"crab resubmit -d {job}")

    # Optionally remove COMPLETED jobs
    if completed_jobs:
        print(f"{BLUE_BOLD}[INFO] Found {len(completed_jobs)} COMPLETED job folders:{RESET}")
        for job in completed_jobs: print(f" - {job}")
        ans = input(f"\n{YELLOW_BOLD}Delete these COMPLETED job folders? (except data) [y/n]: {RESET}").strip().lower()
        if ans in ["y", "yes"]:
            for job in completed_jobs:
                print(f"Deleting {job}...")
                os.system(f"rm -rf '{job}'")
            print(f"{RED_BOLD}Completed jobs removed.{RESET}")

    print(f"\nDone.\nTime taken: {timedelta(seconds=int(elapsed))}\n")

# ------------------------------------------------------------------------------------
def check_voms_proxy():
    result = subprocess.run("voms-proxy-info --timeleft", shell=True, capture_output=True, text=True)
    time_left = result.stdout.strip()
    if result.returncode != 0 or not time_left.isdigit() or int(time_left) <= 0:
        print(f"\n{RED}[WARNING] CMS VOMS proxy not found or expired! Please run the following.{RESET}")
        print("voms-proxy-init -voms cms\n")
        return False
    return True

def check_cmssw():
    cmssw_base = os.environ.get("CMSSW_BASE")
    if not cmssw_base:
        print(f"\n{RED}[WARNING] No CMSSW environment detected! Please set up CMSSW before running.{RESET}\n")
        return False
    return True

# ------------------------------------------------------------------------------------
if __name__ == "__main__":
    if not check_cmssw() or not check_voms_proxy(): pass
    else: check_status_all_jobs()
