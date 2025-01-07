import subprocess
import os

# Get the directory where the script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Change the current working directory to the script's directory
os.chdir(script_dir)

# Automatically find raylib.h in the system's include path
def find_raylib_header():
    # Check common include directories
    include_dirs = [
        "/usr/include",
        "/usr/local/include",
        "/opt/include"
    ]
    
    for dir in include_dirs:
        raylib_header = os.path.join(dir, "raylib.h")
        if os.path.isfile(raylib_header):
            return dir
    return None  # If raylib.h is not found in the directories

# Try to find raylib in standard include directories
raylib_dir = find_raylib_header()

# If raylib.h wasn't found, ask the user for the location
if not raylib_dir:
    print("raylib.h not found in the standard include directories.")
    raylib_dir = input("Please enter the directory where raylib.h is located: ").strip()

    # Check if the directory entered by the user is valid
    if not os.path.isdir(raylib_dir) or not os.path.isfile(os.path.join(raylib_dir, "raylib.h")):
        print("The provided directory does not contain raylib.h. Exiting...")
        exit(1)

# Command to compile the C++ file
command = f"g++ src/main.cpp -o dist/engine -I{raylib_dir} -L/usr/lib -lraylib -lGL -lm -lpthread -ldl -lX11"

# Run the command
try:
    subprocess.run(command, shell=True, check=True)
    print("Compilation successful!")
except subprocess.CalledProcessError as e:
    print(f"An error occurred: \n{e}")
