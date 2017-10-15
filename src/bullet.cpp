#include "bullet.h"

bullet::bullet()
{
    m_dstBullet={0, 0, spriteWidth, spriteHeight};
    m_srcBullet={3*spriteWidth, 4*spriteHeight, spriteWidth, spriteHeight};
    m_state=LIVE;
    m_orientation=NORTH;
    m_speed=bulletSpeed;
}

void bullet::destruct()
{
    m_srcBullet={0*spriteWidth, 4*spriteHeight, spriteWidth, spriteHeight};
    m_srcBullet={1*spriteWidth, 4*spriteHeight, spriteWidth, spriteHeight};
    m_srcBullet={2*spriteWidth, 4*spriteHeight, spriteWidth, spriteHeight};
}

void bullet::movement()
{
    switch(m_orientation)
    {
        case NORTH :
        {
            m_dstBullet.y-=bulletSpeed;
            break;
        }
        case SOUTH :
        {
            m_dstBullet.y+=bulletSpeed;
            break;
        }
        case EAST :
        {
            m_dstBullet.x+=bulletSpeed;
            break;
        }
        case WEST :
        {
            m_dstBullet.x-=bulletSpeed;
            break;
        }
    }
}

void bullet::selectSprite()
{
    switch(m_orientation)
    {
        case NORTH :
        {
            m_srcBullet={0*spriteWidth, 5*spriteHeight, spriteWidth, spriteHeight};
            break;
        }
        case SOUTH :
        {
            m_srcBullet={2*spriteWidth, 5*spriteHeight, spriteWidth, spriteHeight};
            break;
        }
        case EAST :
        {
            m_srcBullet={1*spriteWidth, 5*spriteHeight, spriteWidth, spriteHeight};
            break;
        }
        case WEST :
        {
            m_srcBullet={3*spriteWidth, 5*spriteHeight, spriteWidth, spriteHeight};
            break;
        }
    }
}

bool bullet::checkMapCollision(SDL_Rect **mapArray, char map[ROWS][COLS], int blockType)
{
    for(int rows=0; rows<ROWS; rows++)
    {
        for(int columns=0; columns<COLS; columns++)
        {
            if((SDL_HasIntersection(&m_dstBullet, &mapArray[rows][columns])) &&
              (map[rows][columns]==blockType))
            {
                return true;
            }
        }
    }
    return false;
}
