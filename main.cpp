#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "draw.h"
#include "enemy.h"
#include "gameplay.h"
#include "menu.h"
#include <ctime>
using namespace std;
SDL_Window* gWindow = NULL;
static SDL_Renderer* renderer = NULL;
SDL_Rect C_rect;
SDL_Texture* character;
SDL_Texture* e_slime=NULL;
SDL_Texture* e_ghost=NULL;
Mix_Music* gmusic=NULL;
TTF_Font* font=NULL;
SDL_Color textColor = {255, 255, 255};
draw game;
enemy slime;
enemy ghost;
int cnt_time, sword_time,spawn_time;

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ||IMG_Init(IMG_INIT_JPG) < 0||SDL_INIT_AUDIO<0||TTF_Init()<0)
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
        gWindow = SDL_CreateWindow( "I've Been Killing Slimes for 300 Years", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gmusic = Mix_LoadMUS("music.mp3");
    font = TTF_OpenFont("SFUFuturaBold.TTF",50);
    return success;
}
void spawn_enemy(enemy &e)
{
    if(spawn_time+time_spawn<=clock())
    {
        spawn_time=clock();
        for(int i=0; i<=e_num; i++)
        {
            if(e.check[i]==0)
            {
                e.spawn(game.print,i);
                break;
            }
        }
        if(time_spawn>=100)
        time_spawn-=10;
    }
}
void thanks_mau()
{
    SDL_Rect mau= {0,0,0,0},thanh_mau= {0,0,0,0};
    mau.x=game.print.x+15;
    mau.y=game.print.y+game.print.h-29;
    mau.h=4;
    mau.w=game.print.w*game.health/10-20-10;
    thanh_mau.x=game.print.x+14;
    thanh_mau.h=6;
    thanh_mau.y=game.print.y+game.print.h-30;
    thanh_mau.w=game.print.w-18-10;
    SDL_SetRenderDrawColor(renderer,255,255,255,0);
    SDL_RenderFillRect(renderer,&thanh_mau);
    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_RenderFillRect(renderer,&mau);
    //cout<<thanh_mau.h<<" "<<thanh_mau.w<<" "<<thanh_mau.x<<" "<<thanh_mau.y<<endl;
    SDL_SetRenderDrawColor(renderer,0,0,0,0);
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
        if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)>0)
            Mix_PlayMusic(gmusic,1);
        run_menu(renderer,font,textColor);
        character =IMG_LoadTexture(renderer,"char.png");
        e_slime =IMG_LoadTexture(renderer,"blue_slime1.png");
        e_ghost =IMG_LoadTexture(renderer,"AnimationSheet_Character.png");
        if(e_ghost!=NULL)
            cout<<"clm";
        SDL_QueryTexture(e_slime,0,0,&C_rect.w,&C_rect.h);
        SDL_Event e;
        for(int i=0; i<e_num; i++)
        {
            slime.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
            ghost.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
        }
        while(1)
        {
            SDL_SetRenderDrawColor(renderer,250, 235, 215, 1 );
            SDL_RenderFillRect(renderer,NULL);
            if(game.movex>0)
                SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
            else
                SDL_RenderCopyEx( renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
            spawn_enemy(slime);
            spawn_enemy(ghost);
            for(int i=0; i<slime.num; i++)
            {
                SDL_RenderCopy(renderer, e_slime, &slime.e_rect[i],&slime.printf[i]);
                SDL_RenderCopy(renderer, e_ghost, &ghost.e_rect[i],&ghost.printf[i]);
            }
            thanks_mau();
            SDL_RenderPresent(renderer);
            charmove(e,game,sword_time,slime,ghost);
            if(clock()-20>=cnt_time)
            {
                cnt_time=clock();
                slime.emove(game.print);
                ghost.emove(game.print);
            }
            SDL_RenderClear(renderer);
            SDL_Delay(30);
        }
    }
    return 0;
}


