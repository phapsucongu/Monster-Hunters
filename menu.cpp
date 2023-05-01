#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "menu.h"
#include "enemy.h"
#include "draw.h"
using namespace std;
SDL_Texture* bg=NULL;
SDL_Texture* op=NULL;
SDL_Texture* pau=NULL;
Mix_Chunk* gclick= Mix_LoadWAV("click.wav");
SDL_Rect but_start,but_option,but_quit,but_info,option_pic,but_easy,but_medium,but_hard;
double dame::e_dame=0.5;
int dame::e_step=1;
string text= "I've Been Killing Monster";
string text2= "for 300 Years";
void printText(SDL_Renderer* renderer,string text,int x, int y,TTF_Font* font,SDL_Color textColor)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(),textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = 21*text.size();
    dest.h = 45;
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_DestroyTexture(texture);
 	SDL_FreeSurface(surface);
}
void draw_menu(SDL_Renderer* renderer)
{
    but_start ={470,280,400,110};
    but_option ={470,425,400,110};
    but_quit ={470,555,400,110};
    but_info ={1150,590,65,65};
    option_pic={305,60,720,621};
    but_easy = {510,150,300,95};
    but_medium ={510,320,300,95};
    but_hard = {510,455,300,95};
    bg=IMG_LoadTexture(renderer,"menu.png");
    op=IMG_LoadTexture(renderer,"option.png");
    pau=IMG_LoadTexture(renderer,"pause.png");
    SDL_RenderCopy(renderer,bg,NULL,NULL);
    SDL_RenderPresent(renderer);
}
void option(SDL_Renderer* renderer)
{
    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_RenderCopy(renderer,bg,NULL,NULL);
        SDL_RenderCopy(renderer,op,NULL,&option_pic);
        SDL_RenderPresent(renderer);
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_easy.x&&mouseX<=but_easy.x+but_easy.w&&mouseY>=but_easy.y&&mouseY<=but_easy.y+but_easy.h)
        {
            dame::e_dame=0.5;
            dame::e_step=1;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_medium.x&&mouseX<=but_medium.x+but_medium.w&&mouseY>=but_medium.y&&mouseY<=but_medium.y+but_medium.h)
        {
            dame::e_dame=1;
            dame::e_step=1;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_hard.x&&mouseX<=but_hard.x+but_hard.w&&mouseY>=but_hard.y&&mouseY<=but_hard.y+but_hard.h)
        {
            dame::e_dame=1.5;
            dame::e_step=2;
            Mix_PlayChannel( -1, gclick, 0 );
            cout<<"hard";
            break;
        }
        if(e.type==SDL_QUIT)
            exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
        SDL_RenderClear(renderer);
        SDL_Delay(5);
    }
    //cout<<e_dame;
}
void pause(SDL_Renderer* renderer,int &nani)
{
    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_SetRenderDrawColor(renderer,240, 189, 199, 1 );
        SDL_RenderFillRect(renderer,NULL);
        SDL_RenderCopy(renderer,pau,NULL,&option_pic);
        SDL_RenderPresent(renderer);
        SDL_PollEvent(&e);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_easy.x&&mouseX<=but_easy.x+but_easy.w&&mouseY>=but_easy.y&&mouseY<=but_easy.y+but_easy.h)
        {
            nani=1;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_medium.x&&mouseX<=but_medium.x+but_medium.w&&mouseY>=but_medium.y&&mouseY<=but_medium.y+but_medium.h)
        {
            nani=2;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_hard.x&&mouseX<=but_hard.x+but_hard.w&&mouseY>=but_hard.y&&mouseY<=but_hard.y+but_hard.h)
        {
            nani=3;
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type==SDL_QUIT)
            exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
        SDL_RenderClear(renderer);
        SDL_Delay(5);
    }
}
void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor)
{

    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_PollEvent(&e);
        draw_menu(renderer);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_start.x&&mouseX<=but_start.x+but_start.w&&mouseY>=but_start.y&&mouseY<=but_start.y+but_start.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            break;
        }
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_option.x&&mouseX<=but_option.x+but_option.w&&mouseY>=but_option.y&&mouseY<=but_option.y+but_option.h)
        {
            Mix_PlayChannel( -1, gclick, 0 );
            option(renderer);
        }
        if(e.type==SDL_QUIT||(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=but_quit.x&&mouseX<=but_quit.x+but_quit.w&&mouseY>=but_quit.y&&mouseY<=but_quit.y+but_quit.h))
        {
            Mix_PlayChannel( -1, gclick, 0 );
            exit(0);
        }
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
    }
    //cout<<e_dame;
}
void draw_time(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, Uint32 frametime)
{
    // Set time clock
    string text4 = "Time : ";
    int seconds, minutes;
    seconds = int(frametime)/1000;
    minutes = seconds/60;
    seconds = seconds%60;
    string str_minutes = to_string(minutes);
    string str_seconds = to_string(seconds);
    if(minutes < 10){
        if(seconds < 10){
            text4 = text4 +"0"+ str_minutes +":"+ "0" +str_seconds;
        }
        else{
            text4 = text4 +"0"+ str_minutes +":"+ str_seconds;
        }
    }
    else{
        if(seconds < 10){
            text4 = text4 + str_minutes +":"+ "0" +str_seconds;
        }
        else{
            text4 = text4 + str_minutes +":"+ str_seconds;
        }
    }
    printText(renderer,text4,600,0,font,textColor);
   // SDL_RenderPresent(renderer);
}
void draw_score(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, int score)
{
    // Set score:
    string text3 = "SCORE : ";
    string temp = to_string(score);

    text3 = text3 + temp;

    printText(renderer,text3,0,0,font,textColor);
    SDL_RenderPresent(renderer);
}
