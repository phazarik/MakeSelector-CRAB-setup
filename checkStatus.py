import os, subprocess
import json

def parse_crab_status_output(output):
    ### Initialize default values
    idle, running, transferring, finished, failed = "-", "-", "-", "-", "-"
    status = "-"

    for line in output.splitlines():
        if "Status on the scheduler:" in line: status = line.split("Status on the scheduler:")[-1].strip()
        elif "running" in line:      running      = line.split("running")[-1].strip()
        elif "transferring" in line: transferring = line.split("transferring")[-1].strip()        
        elif "idle" in line:         idle         = line.split("idle")[-1].strip()
        elif "finished" in line:     finished     = line.split("finished")[-1].strip()
        elif "failed" in line:       failed       = line.split("failed")[-1].strip()
    return idle, running, transferring, finished, status

def check_status_all_jobs():
    submitted_dir = "submitted"
    jobid_dict = {}    

    ### Header for display with adjusted column widths
    print(f"\n\033[33m{'No':<3} {'jobname':<50} {'idle':<18} {'running':<18} {'transferring':<18} {'finished':<18} {'status':<18}\033[0m")
    
    ### Iterate over each folder in the submitted directory
    count = 1
    for folder in os.listdir(submitted_dir):
        folder_path = os.path.join(submitted_dir, folder)
        job_name = folder

        process_line = f"crab status -d {folder_path}"
        output = os.popen(process_line).read()  ### Captures the command output
        idle, running, transferring, finished, status = parse_crab_status_output(output)
        if   status == "FAILED":    status = f"\033[31m{status}\033[0m"
        elif status == "COMPLETED": status = f"\033[34m{status}\033[0m"

        print(f"{count:<3} {job_name:<50} {idle:<18} {running:<18} {transferring:<18} {finished:<18} {status:<18}")

        # Extract sample name and job ID, and store it in a JSON
        sample_name = folder.split("crab_nanoSkim_Run3_")[-1]
        job_id = "-"
        for line in output.splitlines():
            if line.startswith("Task name:"):
                job_id_full = line.split()[-1]
                job_id = job_id_full.split(":")[0]
                break
        jobid_dict[sample_name] = job_id

        count += 1

    with open("jobIDs.json", "w") as f: json.dump(jobid_dict, f, indent=4)
    print("")

def check_voms_proxy():
    result = subprocess.run("voms-proxy-info --timeleft", shell=True, capture_output=True, text=True)
    time_left = result.stdout.strip()
    if result.returncode != 0 or not time_left.isdigit() or int(time_left) <= 0:
        print("\n\033[31m[WARNING] CMS VOMS proxy not found or expired! Please run the following.\033[0m")
        print("voms-proxy-init -voms cms\n")
        return False
    
    time_left = int(time_left)
    hours, remainder = divmod(time_left, 3600)
    minutes, seconds = divmod(remainder, 60)
    print(f"CMS VOMS proxy found. Time left: {hours} hours, {minutes} minutes, {seconds} seconds.")
    return True

def check_cmssw():
    cmssw_base = os.environ.get("CMSSW_BASE")
    if not cmssw_base:
        print("\n\033[31m[WARNING] No CMSSW environment detected! Please set up CMSSW before running.\033[0m\n")
        return False
    print(f"CMSSW environment detected: {cmssw_base}")
    return True

### Run the function
if __name__ == "__main__":
    if not check_cmssw() or not check_voms_proxy(): None
    else: check_status_all_jobs()
