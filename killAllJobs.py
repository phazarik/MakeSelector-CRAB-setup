import os, sys

basedir = "submitted"
jobs = os.listdir("submitted")

for job in jobs:
    if not job.startswith("crab_"): continue
    jobpath = os.path.join(basedir, job)
    print(f"\n\033[33mRemoving job: {job}\033[0m")
    processline = f"crab kill -d {jobpath}"
    #print(processline)
    os.system(processline)
    #break ### job

print("\nDone!")
