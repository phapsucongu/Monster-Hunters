#ifndef enemy_h_
#define enemy_h_
//const std::string bgname[6]={"bg1.png","bg2.png","bg3.png","bg4.png","bg5.png","bg6.png"};
#include "draw.h"
const int e_step=4;
class enemy
{
public :
    void spawn(draw nv,int i);
    void emove(draw nv,int i);
    int x,y,num=0;
    SDL_Rect e_rect[10],printf[10];
    int check[10]={0};

};

#endif enemy_h_h;

