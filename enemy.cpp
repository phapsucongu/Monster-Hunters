#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "enemy.h"
<<<<<<< HEAD
#include "draw.h"
=======
#include "draw.h"
>>>>>>> 988f14395bf77f2808985f0f0212804cf2171e8a
#include "menu.h"
#define fi first
#define se second
using namespace std;
int e_map[260][150];
void enemy::spawn(SDL_Rect print,int i)
{
    printf[i]={0,0,30,30};
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
    if(num<=e_num){
        num++;
    }
    check[i]=e_health;
}
void enemy::emove(SDL_Rect print,double &health)
{
    SDL_Rect rect =print;
    rect.x+=30;
    rect.y+=30;
    rect.w-=60;
    rect.h-=60;
    print.x+=print.w/2;
    print.y+=print.h/2;
    for(int i=0;i<num;i++)
<<<<<<< HEAD
    {
        if(collision(printf[i],rect)&&check[i]==1)
        {
            health-=dame::e_dame;
            continue;
=======
    {
        if(collision(printf[i],rect)&&check[i]==1)
        {
            health-=dame::e_dame;
            continue;
>>>>>>> 988f14395bf77f2808985f0f0212804cf2171e8a
        }
        if(abs(printf[i].x-print.x)>=abs(printf[i].y-print.y))
        {
            if(printf[i].x>print.x)
                printf[i].x-=dame::e_step;
            else if(printf[i].x<print.x)
                printf[i].x+=dame::e_step;
            else if(printf[i].y>print.y)
                printf[i].y-=dame::e_step;
            else
                printf[i].y+=dame::e_step;
        }
        else
        {
            if(printf[i].y>print.y)
                printf[i].y-=dame::e_step;
            else if(printf[i].y<print.y)
                printf[i].y+=dame::e_step;
            else if(printf[i].x>print.x)
                printf[i].x-=dame::e_step;
            else
                printf[i].x+=dame::e_step;
        }
    }

}
bool enemy::collision (SDL_Rect a,SDL_Rect b)
{
<<<<<<< HEAD
    a.x+=10;
    a.w-=20;
    a.y+=10;
=======
    a.x+=10;
    a.w-=20;
    a.y+=10;
>>>>>>> 988f14395bf77f2808985f0f0212804cf2171e8a
    a.h-=20;
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
void enemy::reset()
{
    x,y,num=0;
     e_rect[e_num+1],printf[e_num+1];
    for(int i=0;i<=e_num;i++)
    {
        check[i]={0};
        printf[i]={0,0,0,0};

    }

}
int main()
{
    return 0;
}
