# [Lēoht](https://ipa-reader.com/?text=L%C4%93oht&voice=Emma)
A game/graphics engine being made with C++ and Raylib. (Work In Progress)

## Compiling:
Windows 11 will be the only tested Windows version for now.
(Windows 10 should also work just not supported as much or tested)

Linux hasn't been tested yet at all.
(Debian 12 will be tested first soon)

### Windows:

> [!WARNING]
> This won't compile if you use a different path than `C:/raylib` for installing and putting Raylib in path.

- For Windows you will need:
    - [MinGW-x64 installed from winlibs.com](https://winlibs.com/#download-release), [the latest Python installed](https://www.python.org/downloads/) and finnally [Git](https://git-scm.com/) for cloning this repo.

1. Clone this repo using: `git clone https://github.com/monitio/leoht.git`
2. [Download and install Raylib from raylib.com](https://raylib.com).
3. Use [the PATH tutorial](https://windowsloop.com/how-to-add-to-windows-path/) but replace the program/folder it uses with `C:/raylib/`.
4. Then do the [PATH](https://windowsloop.com/how-to-add-to-windows-path/) for `C:/raylib/raylib` and `C:/raylib/raylib/src`.
5. Open the terminal in the folder Git created when cloning called `leoht`.
6. Run [the wcompile.py file](/wcompile.py) with Python 3 by running: `py wcompile.py`
7. Open [the dist folder](/dist/).
8. Run the final finished executable normally called `engine.exe`.

### Linux:

> [!TIP]
> Try and install Python and Raylib through the official sources as much as possible. If your distro doesn't support official packages try look for the most trusted packages or ports from the original packages.

> [!WARNING]
> It is recommended to install Raylib to the default path, `/usr/include`, `/usr/local/include` or `/opt/include`. If it doesn't install to one of those paths then you will need to check where it is through your package manager or where you remember it installing to so you can provide the compile script a valid path. (step 6, error catching).

- For Linux you will need:
    - Download a specific version that has C and C++ (GCC) from [the MinGW-w64 downloads list](https://www.mingw-w64.org/downloads/), [python with the default library](https://pkgs.org/search/?q=python) and finnally [Git](https://git-scm.com/) for cloning this repo.

1. Clone this repo using: `git clone https://github.com/monitio/leoht.git`
2. [Download and install Raylib from a package manager](https://pkgs.org/search/?q=raylib).
4. Open the terminal in the folder Git created when cloning called `leoht`.
5. Run [the lcompile.py file](/lcompile.py) with Python 3 by running: `python3 wcompile.py`
6. (error catching) [The Python script](/lcompile.py) will ask you what path you have for Raylib if it can't find it in the normal paths. 
7. Open [the dist folder](/dist/).
8. Run the final finished executable normally called `engine`.
