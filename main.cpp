#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
#include <ctime>
using namespace std;
//const Uint8* state = SDL_GetKeyboardState(NULL);
SDL_Window* gWindow = NULL;
SDL_Renderer* renderer = NULL;
SDL_Rect C_rect;
SDL_Texture* character;
SDL_Texture* bg;
SDL_Texture* e_slime=NULL;
draw game;
enemy slime;
int cnt_time, sword_time,spawn_time;

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ||IMG_Init(IMG_INIT_JPG) < 0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    return success;
}
void spawn_slime()
{
    if(spawn_time+500<=clock())
            {
                spawn_time=clock();
                for(int i=0; i<=e_num; i++)
                {
                    if(slime.check[i]==0)
                    {
                        slime.spawn(game.print,i);
                        break;
                    }
                }
            }
}
int main( int argc, char* args[] )
{

    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        //bg =IMG_LoadTexture( renderer,"bg.png");
        character =IMG_LoadTexture(renderer,"char.png");
        e_slime =IMG_LoadTexture(renderer,"blue_slime3.png");
        SDL_QueryTexture(e_slime,0,0,&C_rect.w,&C_rect.h);
        SDL_Event e;
        //cout<<C_rect.h<<" "<<C_rect.w;
        for(int i=0; i<19; i++)
        {
            slime.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
        }
        while(1)
        {
            SDL_RenderCopy(renderer, bg, NULL, NULL);
            if(game.movex>0)
                SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
            else
                SDL_RenderCopyEx( renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
            spawn_slime();
            for(int i=0; i<slime.num; i++)
                SDL_RenderCopy(renderer, e_slime, &slime.e_rect[i],&slime.printf[i]);
            SDL_RenderPresent(renderer);
            if(clock()-0>=cnt_time)
            {
                cnt_time=clock();
                charmove(e,game,sword_time,slime);
                slime.emove(game.print);
            }
            SDL_RenderClear(renderer);
            SDL_Delay(30);
        }
    }
    return 0;
}


