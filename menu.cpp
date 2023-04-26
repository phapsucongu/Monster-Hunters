#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "menu.h"
#include "enemy.h"
using namespace std;
SDL_Texture* bg=NULL;
SDL_Texture* start=NULL;
SDL_Texture* quit=NULL;
SDL_Rect button1,button2;
string text= "I've Been Killing Slimes";
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
void draw_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor)
{
    button1 ={100,350,262,73};
    button2 ={140,500,180,73};
    bg=IMG_LoadTexture(renderer,"bg.jpg");
    start=IMG_LoadTexture(renderer,"start.png");
    quit=IMG_LoadTexture(renderer,"quit.png");
    SDL_RenderCopy(renderer,bg,NULL,NULL);
    SDL_RenderCopy(renderer,start,NULL,&button1);
    SDL_RenderCopy(renderer,quit,NULL,&button2);
    printText(renderer,text,100,100,font,textColor);
    printText(renderer,text2,200,150,font,textColor);
    SDL_RenderPresent(renderer);
}
void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor)
{

    int mouseX, mouseY;
    SDL_Event e;
    while(1)
    {
        SDL_PollEvent(&e);
        draw_menu(renderer,font,textColor);
        if(e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=100&&mouseX<=362&&mouseY>=350&&mouseY<=423)
        {
            break;
        }
        if(e.type==SDL_QUIT||e.type == SDL_MOUSEBUTTONDOWN&&mouseX>=140&&mouseX<=320&&mouseY>=500&&mouseY<=573)
            exit(0);
        if(e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.button.x;
            mouseY = e.button.y;
        }
    }
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
