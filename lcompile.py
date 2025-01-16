import subprocess
import os

# Get the directory where the script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Change the current working directory to the script's directory
os.chdir(script_dir)

# Source files
s = "src/main.cpp"
nf = "src/nativeFullscreen/nativeFullscreen.cpp"
rw = "src/refreshWindow/refreshWindow.cpp"

# Include and library paths
si = "-Isrc -Lsrc"

# Attempt to locate raylib headers automatically
def find_raylib_header():
    include_dirs = ["/usr/include", "/usr/local/include", "/opt/include"]
    for dir in include_dirs:
        raylib_header = os.path.join(dir, "raylib.h")
        if os.path.isfile(raylib_header):
            return dir
    return None

raylib_dir = find_raylib_header()

if not raylib_dir:
    print("raylib.h not found in standard include directories.")
    raylib_dir = input("Please enter the directory where raylib.h is located: ").strip()
    if not os.path.isdir(raylib_dir) or not os.path.isfile(os.path.join(raylib_dir, "raylib.h")):
        print("The provided directory does not contain raylib.h. Exiting...")
        exit(1)

# Raylib flags
raylib = f"-I{raylib_dir} -L/usr/lib"

# Executable output
ex = "dist/engine"

# Flags
flags = "-lraylib -lGL -lm -lpthread -ldl -lX11 -Wno-enum-compare"

# Compile command
command = f"g++ {s} {nf} {rw} -o {ex} {si} {raylib} {flags}"

# Run the command
try:
    subprocess.run(command, shell=True, check=True)
    print("Compilation successful!")
except subprocess.CalledProcessError as e:
    print(f"An error occurred: \n{e}")
