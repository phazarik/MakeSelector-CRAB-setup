import os, sys, argparse

parser = argparse.ArgumentParser()
parser.add_argument('--all', action='store_true', help='removes all the output root files in test_outputs')
parser.add_argument('--keepso', action='store_true', help='removes all except the .so library file')
args = parser.parse_args()

script_dir = os.path.dirname(os.path.abspath(__file__))

junk = [
    "*.so",
    "*~",
    "*.pcm",
    "*#",
    "*d",
    "*dict*"
]

if args.all:
    junk.append("test_outputs/*")
if args.keepso:
    junk.remove("*.so")
    junk.remove("*.pcm")

print("Running the following commands ...")
for item in junk:
    full_path = os.path.join(script_dir, item)
    processline = f"rm -rf {full_path}"
    print(processline)
    os.system(processline)
print("Done!")
