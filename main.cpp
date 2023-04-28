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
SDL_Rect mau= {0,0,0,0},thanh_mau= {0,0,0,0};
SDL_Texture* character;
SDL_Texture* e_slime=NULL;
SDL_Texture* e_ghost=NULL;
SDL_Texture* e_ghost2=NULL;
Mix_Music* gmusic=NULL;
TTF_Font* font=NULL;
SDL_Color textColor = {255, 255, 255};
draw game;
enemy slime;
enemy ghost;
enemy ghost2;
Uint32 framestart = SDL_GetTicks();
int cnt_time, sword_time,spawn_time;
int angle = 5,v=1;
bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ||IMG_Init(IMG_INIT_JPG) < 0||SDL_INIT_AUDIO<0||TTF_Init()<0||Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0)
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
void spawn_enemy(enemy &slime, enemy &ghost, enemy &ghost2)
{
    if(spawn_time+time_spawn<=clock())
    {
        spawn_time=clock();
        for(int i=0; i<=e_num; i++)
        {
            if(slime.check[i]==0)
            {
                slime.spawn(game.print,i);
                break;
            }
            if(ghost.check[i]==0&&game.score>=10)
            {
                ghost.spawn(game.print,i);
                break;
            }
            if(ghost2.check[i]==0&&game.score>=20)
            {
                ghost2.spawn(game.print,i);
                break;
            }
        }
        if(time_spawn>=100)
            time_spawn-=20;
    }
}

void draw_enemy()
{
    for(int i=0; i<slime.num; i++)
    {
        SDL_RenderCopyEx(renderer,e_slime, NULL,&slime.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,e_ghost, NULL,&ghost.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,e_ghost2, NULL,&ghost2.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
    }
}
void end_game()
{
    while(1)
    {
        SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
        SDL_RenderFillRect(renderer,NULL);
        draw_enemy();
        if(game.movex>0)
            SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
        else
            SDL_RenderCopyEx(renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderPresent(renderer);
        if(clock()-20>=cnt_time)
        {
            game.die();
            cnt_time=clock();
            slime.emove(game.print,game.health);
            ghost.emove(game.print,game.health);
            ghost2.emove(game.print,game.health);
            if(abs(angle)==5)
                v=-v;
            angle+=v;
        }
        SDL_Event e;
        if(SDL_PollEvent(&e))
            if(e.type==SDL_QUIT)
                exit(0);
        if(game.play==0)
            break;
    }
    game.reset();
    slime.reset();
    ghost.reset();
    ghost2.reset();

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
        character =IMG_LoadTexture(renderer,"char.png");
        e_slime =IMG_LoadTexture(renderer,"ghost.png");
        e_ghost =IMG_LoadTexture(renderer,"cyclops.png");
        e_ghost2 = IMG_LoadTexture(renderer,"monster.png");
        SDL_QueryTexture(e_slime,0,0,&C_rect.w,&C_rect.h);
        SDL_Event e;
        for(int i=0; i<e_num; i++)
        {
            slime.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
            ghost.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
            ghost2.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
        }
        while(1)
        {
            //cout<<game.health<<endl;
            if(!game.play)
            {
                Mix_PlayMusic(gmusic,1);
                run_menu(renderer,font,textColor);
                Mix_HaltMusic();
                game.play=1;
                framestart = SDL_GetTicks();
            }
            //cout<<e_dame<<endl;
            if(game.health<=0)
            {
                end_game();
                continue;
            }
            Uint32 frametime = SDL_GetTicks() - framestart;
            SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
            SDL_RenderFillRect(renderer,NULL);
            if(game.movex>0)
                SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
            else
                SDL_RenderCopyEx(renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
            spawn_enemy(slime,ghost,ghost2);
            draw_enemy();
            thanks_mau(renderer, game, mau, thanh_mau);
            draw_score(renderer, font, textColor, game.score);
            draw_time(renderer,font,textColor,frametime);
            SDL_RenderPresent(renderer);
            charmove(e,game,sword_time,slime, ghost, ghost2);
            if(clock()-20>=cnt_time)
            {
                cnt_time=clock();
                slime.emove(game.print,game.health);
                ghost.emove(game.print,game.health);
                ghost2.emove(game.print,game.health);
                if(abs(angle)==5)
                    v=-v;
                angle+=v;

            }
            SDL_RenderClear(renderer);
            SDL_Delay(30);
        }
    }
    return 0;
}


