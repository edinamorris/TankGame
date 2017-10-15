#ifndef PLAYER_H__
#define PLAYER_H__

#include <iostream>
#include <SDL.h>
#include "gamevalues.h"
#include "turningPoint.h"
#include "bullet.h"

class player
{
public:
    player(Orientation _orientation, SDL_Rect _dstPlayer, SDL_Rect _srcPlayer, int _playerNumber)
          {m_currentOrientation=_orientation; m_dstPlayer=_dstPlayer; m_srcPlayer=_srcPlayer; m_playerNumber=_playerNumber; m_amIDead=false;}
    void draw(SDL_Renderer *ren, SDL_Texture *tex);
    void autoMove(SDL_Rect **mapBlocks, char map[ROWS][COLS], turningPoint *listOfTP);
    void keyboardMove(SDL_Rect **mapBlocks, char map[ROWS][COLS], Direction _direction);
    bool isMovementValid(Orientation _keyPressForward, Orientation _keyPressReverse);
    bool checkMapCollision(SDL_Rect **mapArray, SDL_Rect player, char map[ROWS][COLS], int blockType);
    int calculateTurningPointPos();
    void flipOrientation();
    void correctPosition(int _turningPoint);
    //pass in list of bullets, check if any hit player and are travelling in same direction = hit back of player, delete self and bullet
    void checkBulletCollision(std::vector<bullet> &bulletList);
    void destruct();

    //accessors
    SDL_Rect getDstPlayer(){return m_dstPlayer;}
    SDL_Rect getSrcPlayer(){return m_srcPlayer;}
    Orientation getOrientation(){return m_currentOrientation;}

    //mutators
    void setDstPlayer(SDL_Rect _dstPlayer){m_dstPlayer=_dstPlayer;}
    void setSrcPlayer(SDL_Rect _srcPlayer){m_srcPlayer=_srcPlayer;}
    void setCurrentOrientation(Orientation _orientation){m_currentOrientation=_orientation;}

private:
    Orientation m_currentOrientation;
    SDL_Rect m_dstPlayer;
    SDL_Rect m_srcPlayer;
    int m_playerNumber;
    bool m_amIDead;
};

#endif //PLAYER_H__
