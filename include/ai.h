#ifndef AI_H__
#define AI_H__

#include <iostream>
#include <SDL.h>
#include "gamevalues.h"

class AI
{
public:
    void draw(SDL_Renderer *ren, SDL_Texture *tex);
    bool checkMapCollision();
    void fire();
    void detectHit();
    void destruct();
    void move();
    //accessors
    SDL_Rect getDstAI(){return m_dstAI;}
    SDL_Rect getSrcAI(){return m_srcAI;}
    //mutators
    void setDstAI(SDL_Rect _dstAI){m_dstAI=_dstAI;}
    void setSrcAI(SDL_Rect _srcAI){m_srcAI=_srcAI;}

private:
    Orientation m_currentOrientation;
    Direction m_keyboardInput;
    SDL_Rect m_dstAI;
    SDL_Rect m_srcAI;
};

#endif //AI_H__
