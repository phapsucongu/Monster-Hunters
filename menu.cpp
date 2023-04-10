#include<bits/stdc++.h>
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "menu.h"
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
