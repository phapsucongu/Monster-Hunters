#ifndef enemy_h_
#define enemy_h_
//#include "draw.h"
const int e_step=2;
static int e_num=19;
class enemy
{
public :
    void spawn(SDL_Rect print,int i);
    void emove(SDL_Rect print);
    int x,y,num=0;
    SDL_Rect e_rect[20],printf[20];
    int check[20]={0};
    int e_vs_e(int i,int k);
    bool cmp(int a,int b);
};

#endif enemy_h_h;

