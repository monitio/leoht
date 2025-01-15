import subprocess
import os

# Get the directory where the script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Change the current working directory to the script's directory
os.chdir(script_dir)

# src file
s = "src/main.cpp"

# modules
nf = "src/nativeFullscreen/nativeFullscreen.cpp"
rw = "src/refreshWindow/refreshWindow.cpp"

# imports
si = "-Isrc -Lsrc"

raylib = "-IC:/raylib/raylib/src -LC:/raylib/raylib/src"

# executable output
ex = "dist/engine"

# flags
flags = "-lraylib -lopengl32 -lgdi32 -lwinmm -Wno-enum-compare"

# command = "g++ src/main.cpp src/nativeFullscreen/nativeFullscreen.cpp src/refreshWindow/refreshWindow.cpp src/tutorialModule/tutorialM.cpp -o dist/engine -Isrc -Lsrc -IC:/raylib/raylib/src -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -Wno-enum-compare"
# Command to be executed as a string
command = f"g++ {s} {nf} {rw} -o {ex} {si} {raylib} {flags}"

# Run the command
try:
    subprocess.run(command, shell=True, check=True)
    print("Compilation successful!")
except subprocess.CalledProcessError as e:
    print(f"An error occurred: \n{e}")
