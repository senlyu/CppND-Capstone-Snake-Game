# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

**This project is developed in ubuntu 16.04**

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## New Feature

### Prize, more than just food
Right now we have different type of food, I call it prize, there are different types:
1. Speed Down, color Red- reduce speed
2. Size Shrink, color Green - reduce the size
3. Score More, color yellow - add more score
4. Food, color pink - the normal prize add length of the snake
5. Wall, color blue - add a wall in board
6. Invincible, color light yellow - add a invincible status for the snake, in that status, snake won die

### Wall
Right now we will have 0-4 walls in the board, Wall will be dark bule in board. One wall will be randomly placed on the board if eaten the wall prize. If snake into a wall, game over

### Invincible
If eaten the invincible prize, the snake wont die in next 5 seconds. When snake in invincible mode, the body will be light yellow.

## New files

I have introduced there new classes into the code:
1. board: used to help maintain and validate positions in the board
2. prize: used to implement prize feature
3. wall: used to implement wall features

## Project requirements
### Memory Requirements
#### references
in game.h two function Place and PrizeUpdate used reference in arguements

#### destructors
in game.h used destructors

#### rule of 5
in wall.h used rule of 5

#### move semantics
in game.h and board.h, used move semantics to move wall into board

#### smart pointers
in game.cpp, wall is used in unique_ptr

### Concurrency
in game.cpp, used thread for invicible 5 seconds