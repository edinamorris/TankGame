#ifndef GAMEVALUES_H
#define GAMEVALUES_H

#define ROWS 15  //pacman = 31
#define COLS 15  //pacman = 28
const int spriteWidth=50;
const int spriteHeight=52;
const int BLOCKSIZE=25;
const int playerSpeed=1;
const int bulletSpeed=3;

enum Direction { LEFT, RIGHT, UP, DOWN };
enum Orientation { NORTH, EAST, SOUTH, WEST };
enum bulletState { LIVE, DESTRUCT };

#endif // GAMEVALUES_H
