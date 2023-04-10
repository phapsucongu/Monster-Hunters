#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "enemy.h"
//#include "draw.h"
#define fi first
#define se second
using namespace std;
int e_map[260][150];
void enemy::spawn(SDL_Rect print,int i)
{
    printf[i]={0,0,64,24};
    int x2=0,y2=0;
    if(i%4==1)
    {
        y2=rand()%150 +1;
    }
    if(i%4==2)
    {
        x2=260;
        y2=rand()% 150+1;
    }
    if(i%4==3)
    {
        x2=rand()% 260+1;
    }
    if(i%4==0)
    {
        y2=150;
        x2=rand()%260+1;
    }
    printf[i].x=x2*5;
    printf[i].y=y2*5;
    for(int i=max(0,x2-2);i>=min(259,x2+2);i++)
        for(int j=max(0,y2-2);j>=min(149,y2+2);j++)
            e_map[i][j]=1;
    if(num<=e_num)
        num++;
    //num+=1;
    check[i]=1;
}
void enemy::emove(SDL_Rect print )
{
    for(int i=0;i<num;i++)
    {

        e_rect[i].x+=e_w/7;
        if(e_rect[i].x>=e_w)
            e_rect[i].x=0;
        int r=rand()%10 +1;
        if(r%3)
        {
            if(printf[i].x>print.x)
                printf[i].x-=e_step;
            else if(printf[i].x<print.x)
                printf[i].x+=e_step;
            else if(printf[i].y>print.y)
                printf[i].y-=e_step;
            else
                printf[i].y+=e_step;
        }
        else
        {
            if(printf[i].y>print.y)
                printf[i].y-=e_step;
            else if(printf[i].y<print.y)
                printf[i].y+=e_step;
            else if(printf[i].x>print.x)
                printf[i].x-=e_step;
            else
                printf[i].x+=e_step;
        }
    }
}
bool enemy::collision (SDL_Rect a,SDL_Rect b)
{

    a.x+=30;
    a.w-=60;
    b.x+=30;
    b.w-=60;
    if(a.x>=b.x&&a.x<=b.x+b.w&&a.y>=b.y&&a.y<=b.y+b.h)
        return 1;
    if(a.x+a.w>=b.x&&a.x+a.w<=b.x+b.w&&a.y>=b.y&&a.y<=b.y+b.h)
        return 1;
    if(a.x>=b.x&&a.x<=b.x+b.w&&a.y+a.h>=b.y&&a.y+a.h<=b.y+b.h)
        return 1;
    if(a.x+a.w>=b.x&&a.x+a.w<=b.x+b.w&&a.y+a.h>=b.y&&a.y+a.h<=b.y+b.h)
        return 1;
    return 0;
}

int main()
{
    return 0;
}
