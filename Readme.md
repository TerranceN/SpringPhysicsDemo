Spring Physics Demo
===================

This is just an upload of the project found [here](http://tniechciol.ca/Projects/SpringPhysics/) so that it is easier to browse.

Created by
----------
Terrance Niechciol

TNiechciol@gmail.com

http://TNiechciol.ca

Controls
--------
A       -> Rotate counter-clockwise

D       -> Rotate clockwise

Shift   -> Weaken springs

Space   -> Stiffen springs


Building the game
-----------------
To make the game you need g++ and SFML

### Using g++ directly
Make sure you have g++ (MinGW on Windows, build-essential on Linux), and SFML and enter:
```
g++ -o main.exe src/*.cpp -I path/to/SFML/include -lsfml-window-s -lsfml-system-s -L path/to/SFML/lib -lopengl32 -lglu32 -static-libgcc -static-libstdc++
```

### Using the makefile
#### Common
You need to edit the makefile so the path to SFML for your system is correct.

#### Windows
You need MSYS for make and uname and MinGW for g++.

#### Linux
You need build-essential for g++.

Then just type `make all` to build the game.

