#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "enemy.h"
#include "draw.h"
#define fi first
#define se second
using namespace std;
void enemy::spawn(draw nv,int i)
{
    printf[i]={0,0,144,48};
    int x2=0,y2=0;
    while(1)
    {
        x2=rand()% 1200+40;
        y2=rand()% 700+10;
        if(x2!=nv.print.x||y2!=nv.print.y)
            if(abs(x2-nv.print.x)>=100&&abs(y2-nv.print.y)>=100&&(x2<=300||x2>=900)&&(y2<=200||y2>=500))
            break;
    }
    printf[i].x=x2;
    printf[i].y=y2;
    if(num<=9)
        num++;
    //num+=1;
    check[i]=1;
}
void enemy::emove(draw nv,int i)
{
    if(printf[i].x>=nv.print.x)
        printf[i].x-=e_step;
    if(printf[i].x<=nv.print.x)
        printf[i].x+=e_step;
    if(printf[i].y>=nv.print.y+30)
        printf[i].y-=e_step;
    if(printf[i].y<=nv.print.y+30)
        printf[i].y+=e_step;
}

int main()
{
    return 0;
}
