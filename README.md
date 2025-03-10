# SuperTicTacToe made in C

Super Tic Tac Toe is an advanced version of the classic Tic Tac Toe game, implemented in C using the SDL2 library for graphics and input handling. This project serves as an exercise using SDL2, and C programming.
[Ultimate-Tic-Tac-Toe](https://en.wikipedia.org/wiki/Ultimate_tic-tac-toe)

## In-game Screenshot  
![Screenshot 1](https://github.com/user-attachments/assets/f03bdd56-f7f4-4f5e-bcff-26d0e4ec2513)

## How to compile
The project is built using `CMake`.

### Requirements
To build and run this project, you need:
- A C compiler (e.g., GCC or Clang)
- [SDL2](https://www.libsdl.org/) library installed on your system
- SDL2_image and SDL2_ttf libraries

### Compilation
1. Create a build directory `mkdir build; cd build`
2. Run CMake `cmake ..`
3. Build `cmake --build .`

#### Creating package
To create a `.zip` file use `cmake --build . --target package`