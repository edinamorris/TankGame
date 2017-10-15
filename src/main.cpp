#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "time.h"
#include "player.h"
#include "map.h"
#include "gamevalues.h"
// the width of the screen taking into account the maze and block
#define WIDTH COLS*BLOCKSIZE
// the height of the screen taking into account the maze and block
#define HEIGHT ROWS*BLOCKSIZE

SDL_Rect** createMap();
void createTPList(turningPoint *listOfTP);
void renderBullets(std::vector<bullet> &bulletList, SDL_Renderer *ren, SDL_Texture *tex);
void moveBullets(std::vector<bullet> &bulletList, SDL_Rect **mapBlocks, char map[ROWS][COLS]);
int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        printf("%s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *win = 0;
    win = SDL_CreateWindow("Tank Game", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (win == 0)
    {
        printf("%s\n",SDL_GetError());
        return EXIT_FAILURE;
    }
    // the renderer is the core element we need to draw, each call to SDL for drawing will need the renderer pointer
    SDL_Renderer *ren = 0;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == 0)
    {
        printf("%s\n",SDL_GetError() );
        return EXIT_FAILURE;
    }
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

    SDL_Surface *image;
    image=IMG_Load("spritesheet.bmp");
    if(!image)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        return EXIT_FAILURE;
    }

    /* initialize random seed: */
    srand (time(NULL));

    SDL_Texture *tex = 0;
    tex = SDL_CreateTextureFromSurface(ren, image);
    SDL_FreeSurface(image);

    //Entity creations
    turningPoint *listOfTP = new turningPoint [25];
    createTPList(listOfTP);
    SDL_Rect **mapBlocks=createMap();
    //players - all but player 1 change to AI's when complete
    SDL_Rect player1Dest={1*BLOCKSIZE, 1*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
    SDL_Rect player1Src={0*spriteWidth, 0*spriteHeight, spriteWidth, spriteHeight};
    SDL_Rect player2Dest={13*BLOCKSIZE, 1*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
    SDL_Rect player2Src={0*spriteWidth, 0*spriteHeight, spriteWidth, spriteHeight};
    SDL_Rect player3Dest={13*BLOCKSIZE, 13*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
    SDL_Rect player3Src={0*spriteWidth, 0*spriteHeight, spriteWidth, spriteHeight};
    SDL_Rect player4Dest={1*BLOCKSIZE, 13*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
    SDL_Rect player4Src={0*spriteWidth, 0*spriteHeight, spriteWidth, spriteHeight};
    player player1(EAST, player1Dest, player1Src, 0);
    player player2(SOUTH, player2Dest, player2Src, 1);
    player player3(WEST, player3Dest, player3Src, 2);
    player player4(NORTH, player4Dest, player4Src, 3);
    std::vector<bullet> bulletList;
    bullet newBullet;

    int quit=0;
    while (quit !=1)
    {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);

        //draw map
        for(int rows=0; rows<ROWS; rows++)
        {
            for(int columns=0; columns<COLS; columns++)
            {
                if(map[rows][columns]==1)
                {
                    SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                    SDL_RenderFillRect(ren,&mapBlocks[rows][columns]);
                }
            }
        }

        //player 1
        player1.draw(ren, tex);
        player1.autoMove(mapBlocks, map, listOfTP);
        //player2
        player2.draw(ren, tex);
        player2.autoMove(mapBlocks, map, listOfTP);
        //player 3
        player3.draw(ren, tex);
        player3.autoMove(mapBlocks, map, listOfTP);
        //player 4
        player4.draw(ren, tex);
        player4.autoMove(mapBlocks, map, listOfTP);
        //bullets
        renderBullets(bulletList, ren, tex);

        //call once
        SDL_RenderPresent(ren);

        moveBullets(bulletList, mapBlocks, map);
        player1.checkBulletCollision(bulletList);
        player2.checkBulletCollision(bulletList);
        player3.checkBulletCollision(bulletList);
        player4.checkBulletCollision(bulletList);

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                    {
                        quit=1;
                        break;
                    }
                    case SDLK_UP :
                    {
                        player1.keyboardMove(mapBlocks, map, UP);
                        break;
                    }
                    case SDLK_DOWN :
                    {
                        player1.keyboardMove(mapBlocks, map, DOWN);
                        break;
                    }
                    case SDLK_LEFT :
                    {
                        player1.keyboardMove(mapBlocks, map, LEFT);
                        break;
                    }
                    case SDLK_RIGHT :
                    {
                        player1.keyboardMove(mapBlocks, map, RIGHT);
                        break;
                    }
                    case SDLK_SPACE :
                    {
                        newBullet.setDstBullet(player1.getDstPlayer());
                        newBullet.setOrientation(player1.getOrientation());
                        newBullet.setPlayer(0);
                        newBullet.selectSprite();
                        bulletList.push_back(newBullet);
                        break;
                    }
                }
            }
        }
    }

    delete [] mapBlocks;
    delete [] listOfTP;
    SDL_Quit();
    return EXIT_SUCCESS;
}

void renderBullets(std::vector<bullet> &bulletList, SDL_Renderer *ren, SDL_Texture *tex)
{
    int sizeOfList=bulletList.size();
    for(int i=0; i<sizeOfList; i++)
    {
        SDL_Rect srcBullet=bulletList[i].getSrcBullet();
        SDL_Rect dstBullet=bulletList[i].getDstBullet();
        SDL_RenderCopy(ren, tex, &srcBullet, &dstBullet);
    }
}

//calls all functions needed to loop for bullets
void moveBullets(std::vector<bullet> &bulletList, SDL_Rect **mapBlocks, char map[ROWS][COLS])
{
    int sizeOfList=bulletList.size();
    for(int i=0; i<sizeOfList; i++)
    {
        bulletList[i].movement();
        //collision with walls
        if(bulletList[i].checkMapCollision(mapBlocks, map, 1))
        {
            bulletList[i].setState(DESTRUCT);
            bulletList[i].destruct();
            bulletList.erase(bulletList.begin()+i);
        }
    }
}

void createTPList(turningPoint *listOfTP)
{
    //first row
    listOfTP[0].m_availableOrientations.push_back(EAST);
    listOfTP[0].m_availableOrientations.push_back(SOUTH);
    listOfTP[1].m_availableOrientations.push_back(EAST);
    listOfTP[1].m_availableOrientations.push_back(SOUTH);
    listOfTP[1].m_availableOrientations.push_back(WEST);
    listOfTP[2].m_availableOrientations.push_back(EAST);
    listOfTP[2].m_availableOrientations.push_back(SOUTH);
    listOfTP[2].m_availableOrientations.push_back(WEST);
    listOfTP[3].m_availableOrientations.push_back(EAST);
    listOfTP[3].m_availableOrientations.push_back(SOUTH);
    listOfTP[3].m_availableOrientations.push_back(WEST);
    listOfTP[4].m_availableOrientations.push_back(SOUTH);
    listOfTP[4].m_availableOrientations.push_back(WEST);
    //second row
    listOfTP[5].m_availableOrientations.push_back(NORTH);
    listOfTP[5].m_availableOrientations.push_back(EAST);
    listOfTP[5].m_availableOrientations.push_back(SOUTH);
    listOfTP[6].m_availableOrientations.push_back(NORTH);
    listOfTP[6].m_availableOrientations.push_back(EAST);
    listOfTP[6].m_availableOrientations.push_back(SOUTH);
    listOfTP[6].m_availableOrientations.push_back(WEST);
    listOfTP[7].m_availableOrientations.push_back(NORTH);
    listOfTP[7].m_availableOrientations.push_back(EAST);
    listOfTP[7].m_availableOrientations.push_back(SOUTH);
    listOfTP[7].m_availableOrientations.push_back(WEST);
    listOfTP[8].m_availableOrientations.push_back(NORTH);
    listOfTP[8].m_availableOrientations.push_back(EAST);
    listOfTP[8].m_availableOrientations.push_back(SOUTH);
    listOfTP[8].m_availableOrientations.push_back(WEST);
    listOfTP[9].m_availableOrientations.push_back(NORTH);
    listOfTP[9].m_availableOrientations.push_back(SOUTH);
    listOfTP[9].m_availableOrientations.push_back(WEST);
    //third row
    listOfTP[10].m_availableOrientations.push_back(NORTH);
    listOfTP[10].m_availableOrientations.push_back(EAST);
    listOfTP[10].m_availableOrientations.push_back(SOUTH);
    listOfTP[11].m_availableOrientations.push_back(NORTH);
    listOfTP[11].m_availableOrientations.push_back(EAST);
    listOfTP[11].m_availableOrientations.push_back(SOUTH);
    listOfTP[11].m_availableOrientations.push_back(WEST);
    listOfTP[12].m_availableOrientations.push_back(NORTH);
    listOfTP[12].m_availableOrientations.push_back(EAST);
    listOfTP[12].m_availableOrientations.push_back(SOUTH);
    listOfTP[12].m_availableOrientations.push_back(WEST);
    listOfTP[13].m_availableOrientations.push_back(NORTH);
    listOfTP[13].m_availableOrientations.push_back(EAST);
    listOfTP[13].m_availableOrientations.push_back(SOUTH);
    listOfTP[13].m_availableOrientations.push_back(WEST);
    listOfTP[14].m_availableOrientations.push_back(NORTH);
    listOfTP[14].m_availableOrientations.push_back(SOUTH);
    listOfTP[14].m_availableOrientations.push_back(WEST);
    //fourth row
    listOfTP[15].m_availableOrientations.push_back(NORTH);
    listOfTP[15].m_availableOrientations.push_back(EAST);
    listOfTP[15].m_availableOrientations.push_back(SOUTH);
    listOfTP[16].m_availableOrientations.push_back(NORTH);
    listOfTP[16].m_availableOrientations.push_back(EAST);
    listOfTP[16].m_availableOrientations.push_back(SOUTH);
    listOfTP[16].m_availableOrientations.push_back(WEST);
    listOfTP[17].m_availableOrientations.push_back(NORTH);
    listOfTP[17].m_availableOrientations.push_back(EAST);
    listOfTP[17].m_availableOrientations.push_back(SOUTH);
    listOfTP[17].m_availableOrientations.push_back(WEST);
    listOfTP[18].m_availableOrientations.push_back(NORTH);
    listOfTP[18].m_availableOrientations.push_back(EAST);
    listOfTP[18].m_availableOrientations.push_back(SOUTH);
    listOfTP[18].m_availableOrientations.push_back(WEST);
    listOfTP[19].m_availableOrientations.push_back(NORTH);
    listOfTP[19].m_availableOrientations.push_back(SOUTH);
    listOfTP[19].m_availableOrientations.push_back(WEST);
    //fifth row
    listOfTP[20].m_availableOrientations.push_back(NORTH);
    listOfTP[20].m_availableOrientations.push_back(EAST);
    listOfTP[21].m_availableOrientations.push_back(NORTH);
    listOfTP[21].m_availableOrientations.push_back(EAST);
    listOfTP[21].m_availableOrientations.push_back(WEST);
    listOfTP[22].m_availableOrientations.push_back(NORTH);
    listOfTP[22].m_availableOrientations.push_back(EAST);
    listOfTP[22].m_availableOrientations.push_back(WEST);
    listOfTP[23].m_availableOrientations.push_back(NORTH);
    listOfTP[23].m_availableOrientations.push_back(EAST);
    listOfTP[23].m_availableOrientations.push_back(WEST);
    listOfTP[24].m_availableOrientations.push_back(NORTH);
    listOfTP[24].m_availableOrientations.push_back(WEST);
}

SDL_Rect** createMap()
{
    SDL_Rect **mapBlocks = new SDL_Rect *[ROWS];
    for(int i=0; i<ROWS; i++)
    {
        mapBlocks[i] = new SDL_Rect[COLS];
    }

    for(int rows=0; rows<ROWS; rows++)
    {
        for(int columns=0; columns<COLS; columns++)
        {
             mapBlocks[rows][columns].x=BLOCKSIZE*columns;
             mapBlocks[rows][columns].y=BLOCKSIZE*rows;
             mapBlocks[rows][columns].w=BLOCKSIZE;
             mapBlocks[rows][columns].h=BLOCKSIZE;
        }
    }
    return mapBlocks;
}
