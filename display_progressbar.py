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
RESET = "\033[0m"
RED = "\033[31m"
BLUE = "\033[34m"
YELLOW = "\033[33m"
YELLOW_BOLD = "\033[93m"

COLORS = {
    "idle": "\033[90m",          # gray
    "running": "\033[33m",       # yellow
    "transferring": "\033[36m",  # cyan
    "finished": "\033[34m",      # blue
    "failed": "\033[31m"         # red
}

def parse_crab_status_output(output):
    job_info = {
        "total": 0,
        "idle": 0, "running": 0, "transferring": 0,
        "finished": 0, "failed": 0,
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

        m = re.search(r"(finished|transferring|running|idle|failed)\s+(\d+\.?\d*)%\s+\((\s*\d+)\s*/\s*(\d+)\)", line)
        if m:
            state, pct, count, total = m.groups()
            state = state.strip()
            count = int(count.strip())
            total = int(total.strip())
            percentages[state] = f"{pct}%"
            job_info[state] = count
            job_info["total"] = total

        ## if total is still 0, mark all percentages as "-"
        if job_info["total"] == 0:
            for key in percentages:
                percentages[key] = "0%"

    job_info["percentages"] = percentages
    return job_info

def make_progress_bar(pct, length=25):
    """Build a colorized bar using percentages directly from CRAB output."""
    failed_len = round(float(pct['failed'].replace('%', '')) / 100 * length)
    finished_len = round(float(pct['finished'].replace('%', '')) / 100 * length)
    transf_len = round(float(pct['transferring'].replace('%', '')) / 100 * length)
    running_len = round(float(pct['running'].replace('%', '')) / 100 * length)
    idle_len = length - (failed_len + finished_len + transf_len + running_len)
    bar = ""
    character = "#"
    if failed_len: bar += COLORS['failed'] + character * failed_len + RESET
    if finished_len: bar += COLORS['finished'] + character * finished_len + RESET
    if transf_len: bar += COLORS['transferring'] + character * transf_len + RESET
    if running_len: bar += COLORS['running'] + character * running_len + RESET
    if idle_len: bar += COLORS['idle'] + character * idle_len + RESET
    return f"{bar}{' ' * (30 - length)}"

def colorize_aligned(text, color, width):
    visible_len = len(text)
    return f"{color}{text}{RESET}" + " " * (width - visible_len)

def format_pct(pct):  return f"{pct:<8}"

# helper to replace 0% with '-'
def pct_or_dash(pct_value, color, width):
    if pct_value in ["0%"]: return f"{'-':<{width}}"
    return colorize_aligned(format_pct(pct_value), color, width)

def check_status_all_jobs():
    submitted_dir = "submitted"
    jobid_dict = {}
    failed_jobs = []
    bar_length = 50

    all_folders = [f for f in os.listdir(submitted_dir) if os.path.isdir(os.path.join(submitted_dir, f))]
    max_jobname_len = max((len(f) for f in all_folders), default=10) + 4   # extra padding

    # header spacing widened for clarity
    print(f"\n{YELLOW_BOLD}{'No':<4} {'Job Name':<{max_jobname_len}} {'Progress':<{bar_length+2}} "
          f"{'CRAB':<14} {'Scheduler':<14} {'Total':<8} {'Idle':<8} {'Running':<8} {'Transf':<8} {'Fin':<8} {'Failed':<10}{RESET}")
    
    count = 1
    for folder in sorted(all_folders):
        folder_path = os.path.join(submitted_dir, folder)

        output = os.popen(f"crab status -d {folder_path}").read()
        job_info = parse_crab_status_output(output)
        if job_info["failed"] > 0: failed_jobs.append(folder_path)

        bar = make_progress_bar(job_info['percentages'], bar_length)+"  "
        pct = job_info["percentages"]

        job_id = "-"
        for line in output.splitlines():
            if line.startswith("Task name:"):
                job_id_full = line.split()[-1]
                job_id = job_id_full.split(":")[0]
                break
            
        sample_name = folder.split("crab_nanoSkim_Run3_")[-1]
        jobid_dict[sample_name] = job_id

        crab_status = f"{job_info['CRAB']:<13}"
        scheduler_status_raw = job_info["Scheduler"]
        if scheduler_status_raw == "COMPLETED": scheduler_status = colorize_aligned("COMPLETED", BLUE, 13)
        else: scheduler_status = f"{scheduler_status_raw:<13}"
    
        idle_colored  = pct_or_dash(pct['idle'],         COLORS["idle"],         9)
        run_colored   = pct_or_dash(pct['running'],      COLORS["running"],      9)
        trans_colored = pct_or_dash(pct['transferring'], COLORS["transferring"], 9)
        fin_colored   = pct_or_dash(pct['finished'],     COLORS["finished"],     9)
        fail_colored  = pct_or_dash(pct['failed'],       COLORS["failed"],       9)
        
        print(f"{count:<4} {folder:<{max_jobname_len}} {bar:<{bar_length+2}} "
              f"{crab_status}  {scheduler_status}  "
              f"{job_info['total']:<8} "
              f"{idle_colored}{run_colored}{trans_colored}{fin_colored}{fail_colored}")

        count += 1

    with open("jobIDs.json", "w") as f: json.dump(jobid_dict, f, indent=4)

    # === Print resubmit commands if needed ===
    if failed_jobs:
        print(f"\n{RED}[INFO] Found failed jobs. Suggested resubmit commands:{RESET}")
        for job in failed_jobs: print(f"crab resubmit -d {job}")
    print("")


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

if __name__ == "__main__":
    if not check_cmssw() or not check_voms_proxy(): pass
    else: check_status_all_jobs()
