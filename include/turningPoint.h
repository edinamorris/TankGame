#ifndef TURNINGPOINT_H__
#define TURNINGPOINT_H__

#include <iostream>
#include <SDL.h>
#include "gamevalues.h"
#include <vector>

class turningPoint
{
public:
    turningPoint();
    std::vector<Orientation> m_availableOrientations;

    //function pass in current orientation from player when collision with wall, return orientation to move
    Orientation getNewOrientation(Orientation _currentOrientation);
    //removes element from std::vector
    void deleteCurrentOrientation(Orientation _currentOrientation);

    //accessors
    SDL_Rect getDestination(){return m_dstTP;}
    SDL_Rect getSourc(){return m_srcTP;}
    //mutators
    void setDestination(SDL_Rect _destination){m_dstTP=_destination;}
    void setSource(SDL_Rect _source){m_srcTP=_source;}

private:
    SDL_Rect m_dstTP;
    SDL_Rect m_srcTP;
};

#endif //TURNINGPOINT_H__
