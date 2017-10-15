#ifndef BULLET_H__
#define BULLET_H__

#include <iostream>
#include <SDL.h>
#include "gamevalues.h"

class bullet
{
public:
    bullet();
    void movement();
    void selectSprite();
    bool checkMapCollision(SDL_Rect **mapArray, char map[ROWS][COLS], int blockType);
    //may not be needed
    void destruct();

    //accessors
    SDL_Rect getDstBullet(){return m_dstBullet;}
    SDL_Rect getSrcBullet(){return m_srcBullet;}
    bulletState getState(){return m_state;}
    Orientation getOrientation(){return m_orientation;}
    int getSpeed(){return m_speed;}
    int getPlayer(){return m_player;}

    //mutators
    void setDstBullet(SDL_Rect _dstBullet){m_dstBullet=_dstBullet;}
    void setSrcBullet(SDL_Rect _srcBullet){m_srcBullet=_srcBullet;}
    void setState(bulletState _state){m_state=_state;}
    void setOrientation(Orientation _orientation){m_orientation=_orientation;}
    void setSpeed(int _speed){m_speed=_speed;}
    void setPlayer(int _player){m_player=_player;}

private:
    SDL_Rect m_dstBullet;
    SDL_Rect m_srcBullet;
    bulletState m_state;
    Orientation m_orientation;
    int m_speed;
    int m_player;
};

#endif //BULLET_H__
