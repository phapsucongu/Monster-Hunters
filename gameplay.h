#ifndef gameplay_h_
#define gameplay_h_
#include "draw.h"
#include "enemy.h"
//#include <bits/stdc++.h>
void destroy(draw &nv,enemy &slime);
void charmove(SDL_Event e, draw &game,int &sword_time,enemy &slime,enemy &ghost, enemy &ghost2);
void sword(enemy &slime, draw &game);
void thanks_mau(SDL_Renderer* renderer, draw &game, SDL_Rect &mau,SDL_Rect &thanh_mau);
void collision (draw &nv, enemy &slime);
int check(SDL_Rect a, SDL_Rect b);
const int range_attack=96;
#endif gameplay_h_h;
