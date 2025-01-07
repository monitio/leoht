import subprocess
import os

# Get the directory where the script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Change the current working directory to the script's directory
os.chdir(script_dir)

# Command to be executed as a string
command = "g++ src/main.cpp -o dist/engine -IC:/raylib/raylib/src -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm"

# Run the command
try:
    subprocess.run(command, shell=True, check=True)
    print("Compilation successful!")
except subprocess.CalledProcessError as e:
    print(f"An error occurred: \n{e}")
