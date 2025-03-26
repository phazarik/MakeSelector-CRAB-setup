import subprocess
import ast

def run_command(cmd):
    print(f"Running command: {cmd}")
    result = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    full_output = result.stdout + result.stderr
    return full_output.strip()

def extract_xsec(output):
    for line in output.split("\n"):
        if "After matching: total cross section" in line:
            parts = line.split("=")
            parts = [p.strip() for p in parts]
            if len(parts) > 1: return parts[1]
    return "No cross-section found."

def process_dataset(name, dataset):
    print(f"\033[33mProcessing: {dataset}\033[0m")

    ### Finding parent dataset
    parent_cmd = f"dasgoclient --query=\"parent dataset={dataset}\""
    parent_dataset = run_command(parent_cmd)
    if not parent_dataset:
        print(f"\033[31mError: No parent dataset found for {dataset}\033[0m")
        return
    print("Found parent dataset:", parent_dataset)

    ### Finding parent file
    file_cmd = f"dasgoclient --query=\"file dataset={parent_dataset}\" | head -n 1"
    miniAOD_file = run_command(file_cmd)
    if not miniAOD_file:
        print(f"\033[31mError: No MiniAOD file found for {parent_dataset}\033[0m")
        return
    print("Found MiniAOD file:", miniAOD_file)

    ### Running ana.py
    cmsRun_cmd = f"cmsRun ana.py inputFiles=file:root://cms-xrd-global.cern.ch//{miniAOD_file}"
    cmsRun_output = run_command(cmsRun_cmd)
    xsec_line = extract_xsec(cmsRun_output)
    print(f"\n\033[93m{xsec_line}\033[0m")

def main():

    ### Checking voms-proxy
    result = subprocess.run("voms-proxy-info --timeleft", shell=True, capture_output=True, text=True)
    time_left = result.stdout.strip()
    if result.returncode != 0 or not time_left.isdigit() or int(time_left) <= 0:
        print("\n\033[91m[WARNING] CMS VOMS proxy not found or expired! Please run the following.\033[0m")
        print("voms-proxy-init -voms cms")
        return
    
    time_left = int(time_left)
    hours, remainder = divmod(time_left, 3600)
    minutes, seconds = divmod(remainder, 60)
    print(f"CMS VOMS proxy found. Time left: {int(hours)} hours, {int(minutes)} minutes, {int(seconds)} seconds.")
    
    samples=[]
    with open("../samplelist_run3summer22.txt", "r") as file: content = file.read().strip()
    samples = ast.literal_eval(content)
    for name, dataset, flag in samples:
        print('\n'+'-'*150)
        process_dataset(name, dataset)
        #break

    print('\nDone!\n')

if __name__ == "__main__": main()
