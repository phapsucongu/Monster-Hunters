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
SDL_Texture* boss=NULL;
Mix_Music* gmusic=NULL;
Mix_Chunk* sword_sound=NULL;
TTF_Font* font=NULL;
SDL_Color textColor = {255, 255, 255};
int frametime;
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
        gWindow = SDL_CreateWindow( "I've Been Killing Monsters for 300 Years", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    gmusic = Mix_LoadMUS("sound/music.mp3");
    font = TTF_OpenFont("font/ThaleahFat.ttf",50);
    sword_sound = Mix_LoadWAV("sound/sword_sound.wav");
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
        if(i==0&&dame::lv==3)
        {
            SDL_RenderCopyEx(renderer,boss, NULL,&slime.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderCopyEx(renderer,e_ghost, NULL,&ghost.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderCopyEx(renderer,e_ghost2, NULL,&ghost2.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        }
        else{
        SDL_RenderCopyEx(renderer,e_slime, NULL,&slime.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,e_ghost, NULL,&ghost.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        SDL_RenderCopyEx(renderer,e_ghost2, NULL,&ghost2.printf[i], angle, NULL, SDL_FLIP_HORIZONTAL);
        }
    }
}
void end_game()
{
    while(1)
    {
        SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
        SDL_RenderFillRect(renderer,NULL);
        printText(renderer,"YOU LOSE",580,250,font,textColor);
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
void render()
{
    frametime = SDL_GetTicks() - framestart;
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
}
void but_pause()
{
    int get_pause=SDL_GetTicks();
    int nani=0;
    pause(renderer,nani);
    if(nani==1)
    {
        game.reset();
        slime.reset();
        ghost.reset();
        ghost2.reset();
        game.play=1;
        framestart = SDL_GetTicks();
    }
    if(nani==2)
    {
        game.play=1;
        framestart+=SDL_GetTicks()-get_pause;
    }
    if(nani==3)
    {
        game.play=0;
        game.reset();
        slime.reset();
        ghost.reset();
        ghost2.reset();
        framestart = SDL_GetTicks();
    }
}
void areyouwinningson()
{
    if(dame::lv==1)
    {
        if((game.score>=20&&frametime>=120000)||game.score>=40)
        {
            game.play=0;
            game.reset();
            slime.reset();
            ghost.reset();
            ghost2.reset();
            framestart = SDL_GetTicks();
            int t=5000;
            while(t--)
            {
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                if(game.movex>0)
                    SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
                else
                    SDL_RenderCopyEx(renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
                printText(renderer,"YOU WIN",580,250,font,textColor);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

        }
    }
    if(dame::lv==2)
    {
        if((game.score>=30&&frametime>=180000)||game.score>=60)
        {
            game.play=0;
            game.reset();
            slime.reset();
            ghost.reset();
            ghost2.reset();
            framestart = SDL_GetTicks();
            int t=5000;
            while(t--)
            {
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                if(game.movex>0)
                    SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
                else
                    SDL_RenderCopyEx(renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
                printText(renderer,"YOU WIN",580,250,font,textColor);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

        }
    }
    if(dame::lv==3)
    {
        if((game.score>=50&&frametime>=250000)||game.score>=100)
        {
            game.play=0;
            game.reset();
            slime.reset();
            ghost.reset();
            ghost2.reset();
            framestart = SDL_GetTicks();
            int t=5000;
            while(t--)
            {
                SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
                SDL_RenderFillRect(renderer,NULL);
                if(game.movex>0)
                    SDL_RenderCopy(renderer, character, &game.cc_rect,&game.print);
                else
                    SDL_RenderCopyEx(renderer,character, &game.cc_rect, &game.print, 0, NULL, SDL_FLIP_HORIZONTAL);
                printText(renderer,"YOU WIN",580,250,font,textColor);
                SDL_RenderPresent(renderer);
                SDL_RenderClear(renderer);
            }

        }
    }
}
int main( int argc, char* args[] )
{

    if( !init() )
        printf( "Failed to initialize!\n" );
    else
    {
        renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
        character =IMG_LoadTexture(renderer,"image/char.png");
        e_slime =IMG_LoadTexture(renderer,"image/ghost.png");
        e_ghost =IMG_LoadTexture(renderer,"image/cyclops.png");
        e_ghost2 = IMG_LoadTexture(renderer,"image/monster.png");
        boss=IMG_LoadTexture(renderer,"image/boss.png");
        slime.e_health=1;
        ghost.e_health=2;
        ghost2.e_health=3;
        SDL_Event e;
        for(int i=0; i<e_num; i++)
        {
            slime.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
            ghost.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
            ghost2.e_rect[i]= {0,0,C_rect.w/6,C_rect.h};
        }
        while(1)
        {
            if(!game.play)
            {
                Mix_PlayMusic(gmusic,1);
                run_menu(renderer,font,textColor);
                Mix_HaltMusic();
                game.play=1;
                framestart = SDL_GetTicks();
                if(dame::lv==3)
                {
                    slime.check[0]=100;
                    slime.printf[0]={0,0,132,88};
                }
            }
            if(game.play==2)
            {
                but_pause();
            }
            if(game.health<=0)
            {
                end_game();
                continue;
            }
            if(game.action==1){
                Mix_HaltChannel(-1);
                Mix_PlayChannel( -1, sword_sound, 0 );
                game.action==2;
            }
            areyouwinningson();
            render();
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
            charmove(e,game,sword_time,slime, ghost, ghost2);
            SDL_RenderClear(renderer);
            SDL_Delay(30);
        }
    }
    return 0;
}

