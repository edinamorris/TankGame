#include "player.h"

void player::draw(SDL_Renderer *ren, SDL_Texture *tex)
{
    SDL_RenderCopy(ren, tex, &m_srcPlayer, &m_dstPlayer);
}

void player::autoMove(SDL_Rect **mapBlocks, char map[ROWS][COLS], turningPoint *listOfTP)
{
    if(m_amIDead==false)
    {
        switch(m_currentOrientation)
        {
            case EAST :
            {
                m_dstPlayer.x+=playerSpeed;
                m_srcPlayer.x=1*spriteWidth;
                m_srcPlayer.y=m_playerNumber*spriteHeight;
                if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                {
                    m_dstPlayer.x-=playerSpeed;
                    int currentTurningPoint=calculateTurningPointPos();
                    flipOrientation();
                    m_currentOrientation=listOfTP[currentTurningPoint].getNewOrientation(m_currentOrientation);
                }
                break;
            }
            case SOUTH :
            {
                m_dstPlayer.y+=playerSpeed;
                m_srcPlayer.x=2*spriteWidth;
                m_srcPlayer.y=m_playerNumber*spriteHeight;
                if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                {
                    m_dstPlayer.y-=playerSpeed;
                    int currentTurningPoint=calculateTurningPointPos();
                    flipOrientation();
                    m_currentOrientation=listOfTP[currentTurningPoint].getNewOrientation(m_currentOrientation);
                }
                break;
            }
            case WEST :
            {
                m_dstPlayer.x-=playerSpeed;
                m_srcPlayer.x=3*spriteWidth;
                m_srcPlayer.y=m_playerNumber*spriteHeight;
                if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                {
                    m_dstPlayer.x+=playerSpeed;
                    int currentTurningPoint=calculateTurningPointPos();
                    flipOrientation();
                    m_currentOrientation=listOfTP[currentTurningPoint].getNewOrientation(m_currentOrientation);
                }
                break;
            }
            case NORTH :
            {
                m_dstPlayer.y-=playerSpeed;
                m_srcPlayer.x=0*spriteWidth;
                m_srcPlayer.y=m_playerNumber*spriteHeight;
                if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                {
                    m_dstPlayer.y+=playerSpeed;
                    int currentTurningPoint=calculateTurningPointPos();
                    flipOrientation();
                    m_currentOrientation=listOfTP[currentTurningPoint].getNewOrientation(m_currentOrientation);
                }
                break;
            }
        }
    }
}

void player::keyboardMove(SDL_Rect **mapBlocks, char map[ROWS][COLS], Direction _direction)
{
    if(m_amIDead==false)
    {
        //only allow keyboard input when at turning point "2" on map.h
        if(checkMapCollision(mapBlocks, m_dstPlayer, map, 2)==true)
        {
            int currentTurningPoint=calculateTurningPointPos();
            correctPosition(currentTurningPoint);
            switch (_direction)
            {
                case UP :
                {
                    if(isMovementValid(NORTH, SOUTH))
                    {
                        m_currentOrientation=NORTH;
                        m_dstPlayer.y-=playerSpeed;
                        m_srcPlayer.x=0*spriteWidth;
                        m_srcPlayer.y=m_playerNumber*spriteHeight;
                        if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                        {
                            m_dstPlayer.y+=playerSpeed;
                        }
                        break;
                    }
                    break;
                }
                case DOWN :
                {
                    if(isMovementValid(SOUTH, NORTH))
                    {
                        m_currentOrientation=SOUTH;
                        m_dstPlayer.y+=playerSpeed;
                        m_srcPlayer.x=2*spriteWidth;
                        m_srcPlayer.y=m_playerNumber*spriteHeight;
                        if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                        {
                            m_dstPlayer.y-=playerSpeed;
                        }
                        break;
                    }
                    break;
                }
                case LEFT :
                {
                    if(isMovementValid(WEST, EAST))
                    {
                        m_currentOrientation=WEST;
                        m_dstPlayer.x-=playerSpeed;
                        m_srcPlayer.x=3*spriteWidth;
                        m_srcPlayer.y=m_playerNumber*spriteHeight;
                        if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                        {
                            m_dstPlayer.x+=playerSpeed;
                        }
                        break;
                    }
                    break;
                }
                case RIGHT :
                {
                    if(isMovementValid(EAST, WEST))
                    {
                        m_currentOrientation=EAST;
                        m_dstPlayer.x+=playerSpeed;
                        m_srcPlayer.x=1*spriteWidth;
                        m_srcPlayer.y=m_playerNumber*spriteHeight;
                        if(checkMapCollision(mapBlocks, m_dstPlayer, map,1)==true)
                        {
                            m_dstPlayer.x-=playerSpeed;
                        }
                        break;
                    }
                    break;
                }
            }
        }
    }
}

bool player::isMovementValid(Orientation _keyPressForward, Orientation _keyPressReverse)
{
    bool result=true;

    if((_keyPressForward==m_currentOrientation) || (_keyPressReverse==m_currentOrientation))
    {
        return false;
    }

    return result;
}

bool player::checkMapCollision(SDL_Rect **mapArray, SDL_Rect player, char map[ROWS][COLS], int blockType)
{
    for(int rows=0; rows<ROWS; rows++)
    {
        for(int columns=0; columns<COLS; columns++)
        {
            if((SDL_HasIntersection(&player, &mapArray[rows][columns])) &&
              (map[rows][columns]==blockType))
            {
                return true;
            }
        }
    }
    return false;
}

//calculates which TP number tank is in based on m_dstPlayer.x and y - ?TODO change to algorithm?
int player::calculateTurningPointPos()
{
    int currentTurningPoint=0;

    //first row
    if((m_dstPlayer.x>=10 && m_dstPlayer.x<=65) && (m_dstPlayer.y>=10 && m_dstPlayer.y<=65))
    {
        currentTurningPoint=0;
    }
    else if((m_dstPlayer.x>=85 && m_dstPlayer.x<=140) && (m_dstPlayer.y>=10 && m_dstPlayer.y<=65))
    {
        currentTurningPoint=1;
    }
    else if((m_dstPlayer.x>=160 && m_dstPlayer.x<=215) && (m_dstPlayer.y>=10 && m_dstPlayer.y<=65))
    {
        currentTurningPoint=2;
    }
    else if((m_dstPlayer.x>=235 && m_dstPlayer.x<=290) && (m_dstPlayer.y>=10 && m_dstPlayer.y<=65))
    {
        currentTurningPoint=3;
    }
    else if((m_dstPlayer.x>=310 && m_dstPlayer.x<=365) && (m_dstPlayer.y>=10 && m_dstPlayer.y<=65))
    {
        currentTurningPoint=4;
    }
    //second row
    else if((m_dstPlayer.x>=10 && m_dstPlayer.x<=65) && (m_dstPlayer.y>=85 && m_dstPlayer.y<=140))
    {
        currentTurningPoint=5;
    }
    else if((m_dstPlayer.x>=85 && m_dstPlayer.x<=140) && (m_dstPlayer.y>=85 && m_dstPlayer.y<=140))
    {
        currentTurningPoint=6;
    }
    else if((m_dstPlayer.x>=160 && m_dstPlayer.x<=215) && (m_dstPlayer.y>=85 && m_dstPlayer.y<=140))
    {
        currentTurningPoint=7;
    }
    else if((m_dstPlayer.x>=235 && m_dstPlayer.x<=290) && (m_dstPlayer.y>=85 && m_dstPlayer.y<=140))
    {
        currentTurningPoint=8;
    }
    else if((m_dstPlayer.x>=310 && m_dstPlayer.x<=365) && (m_dstPlayer.y>=85 && m_dstPlayer.y<=140))
    {
        currentTurningPoint=9;
    }
    //third row
    else if((m_dstPlayer.x>=10 && m_dstPlayer.x<=65) && (m_dstPlayer.y>=160 && m_dstPlayer.y<=215))
    {
        currentTurningPoint=10;
    }
    else if((m_dstPlayer.x>=85 && m_dstPlayer.x<=140) && (m_dstPlayer.y>=160 && m_dstPlayer.y<=215))
    {
        currentTurningPoint=11;
    }
    else if((m_dstPlayer.x>=160 && m_dstPlayer.x<=215) && (m_dstPlayer.y>=160 && m_dstPlayer.y<=215))
    {
        currentTurningPoint=12;
    }
    else if((m_dstPlayer.x>=235 && m_dstPlayer.x<=290) && (m_dstPlayer.y>=160 && m_dstPlayer.y<=215))
    {
        currentTurningPoint=13;
    }
    else if((m_dstPlayer.x>=310 && m_dstPlayer.x<=365) && (m_dstPlayer.y>=160 && m_dstPlayer.y<=215))
    {
        currentTurningPoint=14;
    }
    //fourth row
    else if((m_dstPlayer.x>=10 && m_dstPlayer.x<=65) && (m_dstPlayer.y>=235 && m_dstPlayer.y<=290))
    {
        currentTurningPoint=15;
    }
    else if((m_dstPlayer.x>=85 && m_dstPlayer.x<=140) && (m_dstPlayer.y>=235 && m_dstPlayer.y<=290))
    {
        currentTurningPoint=16;
    }
    else if((m_dstPlayer.x>=160 && m_dstPlayer.x<=215) && (m_dstPlayer.y>=235 && m_dstPlayer.y<=290))
    {
        currentTurningPoint=17;
    }
    else if((m_dstPlayer.x>=235 && m_dstPlayer.x<=290) && (m_dstPlayer.y>=235 && m_dstPlayer.y<=290))
    {
        currentTurningPoint=18;
    }
    else if((m_dstPlayer.x>=310 && m_dstPlayer.x<=365) && (m_dstPlayer.y>=235 && m_dstPlayer.y<=290))
    {
        currentTurningPoint=19;
    }
    //fifth row
    else if((m_dstPlayer.x>=10 && m_dstPlayer.x<=65) && (m_dstPlayer.y>=310 && m_dstPlayer.y<=365))
    {
        currentTurningPoint=20;
    }
    else if((m_dstPlayer.x>=85 && m_dstPlayer.x<=140) && (m_dstPlayer.y>=310 && m_dstPlayer.y<=365))
    {
        currentTurningPoint=21;
    }
    else if((m_dstPlayer.x>=160 && m_dstPlayer.x<=215) && (m_dstPlayer.y>=310 && m_dstPlayer.y<=365))
    {
        currentTurningPoint=22;
    }
    else if((m_dstPlayer.x>=235 && m_dstPlayer.x<=290) && (m_dstPlayer.y>=310 && m_dstPlayer.y<=365))
    {
        currentTurningPoint=23;
    }
    else if((m_dstPlayer.x>=310 && m_dstPlayer.x<=365) && (m_dstPlayer.y>=310 && m_dstPlayer.y<=365))
    {
        currentTurningPoint=24;
    }

    return currentTurningPoint;
}

//TODO - ?change to algorithm? - this is to avoid collision problems with keypress inaccuracies
void player::correctPosition(int _turningPoint)
{
    switch(_turningPoint)
    {
        case 0 :
        {
            m_dstPlayer.x=25;
            m_dstPlayer.y=25;
            break;
        }
        case 1 :
        {
            m_dstPlayer.x=100;
            m_dstPlayer.y=25;
            break;
        }
        case 2 :
        {
            m_dstPlayer.x=175;
            m_dstPlayer.y=25;
            break;
        }
        case 3 :
        {
            m_dstPlayer.x=250;
            m_dstPlayer.y=25;
            break;
        }
        case 4 :
        {
            m_dstPlayer.x=325;
            m_dstPlayer.y=25;
            break;
        }
        case 5 :
        {
            m_dstPlayer.x=25;
            m_dstPlayer.y=100;
            break;
        }
        case 6 :
        {
            m_dstPlayer.x=100;
            m_dstPlayer.y=100;
            break;
        }
        case 7 :
        {
            m_dstPlayer.x=175;
            m_dstPlayer.y=100;
            break;
        }
        case 8 :
        {
            m_dstPlayer.x=250;
            m_dstPlayer.y=100;
            break;
        }
        case 9 :
        {
            m_dstPlayer.x=325;
            m_dstPlayer.y=100;
            break;
        }
        case 10 :
        {
            m_dstPlayer.x=25;
            m_dstPlayer.y=175;
            break;
        }
        case 11 :
        {
            m_dstPlayer.x=100;
            m_dstPlayer.y=175;
            break;
        }
        case 12 :
        {
            m_dstPlayer.x=175;
            m_dstPlayer.y=175;
            break;
        }
        case 13 :
        {
            m_dstPlayer.x=250;
            m_dstPlayer.y=175;
            break;
        }
        case 14 :
        {
            m_dstPlayer.x=325;
            m_dstPlayer.y=175;
            break;
        }
        case 15 :
        {
            m_dstPlayer.x=25;
            m_dstPlayer.y=250;
            break;
        }
        case 16 :
        {
            m_dstPlayer.x=100;
            m_dstPlayer.y=250;
            break;
        }
        case 17 :
        {
            m_dstPlayer.x=175;
            m_dstPlayer.y=250;
            break;
        }
        case 18 :
        {
            m_dstPlayer.x=250;
            m_dstPlayer.y=250;
            break;
        }
        case 19 :
        {
            m_dstPlayer.x=325;
            m_dstPlayer.y=250;
            break;
        }
        case 20 :
        {
            m_dstPlayer.x=25;
            m_dstPlayer.y=325;
            break;
        }
        case 21 :
        {
            m_dstPlayer.x=100;
            m_dstPlayer.y=325;
            break;
        }
        case 22 :
        {
            m_dstPlayer.x=175;
            m_dstPlayer.y=325;
            break;
        }
        case 23 :
        {
            m_dstPlayer.x=250;
            m_dstPlayer.y=325;
            break;
        }
        case 24 :
        {
            m_dstPlayer.x=325;
            m_dstPlayer.y=325;
            break;
        }
    }
}

//to stop tank from going backwards on itself
void player::flipOrientation()
{
    switch(m_currentOrientation)
    {
        case EAST :
        {
            m_currentOrientation=WEST;
            break;
        }
        case SOUTH :
        {
            m_currentOrientation=NORTH;
            break;
        }
        case WEST :
        {
            m_currentOrientation=EAST;
            break;
        }
        case NORTH :
        {
            m_currentOrientation=SOUTH;
            break;
        }
    }
}

//need to ensure not checking own bullets
void player::checkBulletCollision(std::vector<bullet> &bulletList)
{
    int sizeOfList=bulletList.size();
    for(int i=0; i<sizeOfList; i++)
    {
        SDL_Rect bulletDst=bulletList[i].getDstBullet();
        int bulletOwner=bulletList[i].getPlayer();
        Orientation bulletOrientation=bulletList[i].getOrientation();

        if(SDL_HasIntersection(&m_dstPlayer, &bulletDst) &&
          (m_playerNumber!=bulletOwner) &&
          (m_currentOrientation==bulletOrientation))
        {
            bulletList[i].setState(DESTRUCT);
            bulletList[i].destruct();
            bulletList.erase(bulletList.begin()+i);
            destruct();
        }
    }
}

void player::destruct()
{
    std::cout<<"Tank"<<m_playerNumber<<" destroyed!\n";
    m_dstPlayer={15*BLOCKSIZE, 15*BLOCKSIZE, spriteWidth, spriteHeight};
    m_amIDead=true;
}
