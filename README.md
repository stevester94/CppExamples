# What to install
sudo apt install libboost1.71-dev

# How to add new examples
Just create a dir. If it has a cpp file in it, it'll get compiled.
- _toolbox dir gets included automatically


# Custom compiler flags
If the makefile encounters a file `flags.txt` it'll stick that text as the flags for g++ (note that the include path for helpers is always included)