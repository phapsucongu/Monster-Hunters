#ifndef gameplay_h_
#define gameplay_h_
#include "draw.h"
#include "enemy.h"
//#include <bits/stdc++.h>
void destroy(draw &nv,enemy &slime);
void charmove(SDL_Event e, draw &game,int &sword_time,enemy &slime);
void sword(enemy &slime, draw &game);
void collision (draw &nv, enemy &slime);
int check(SDL_Rect a, SDL_Rect b);
const int range_attack=50;

#endif gameplay_h_h;
