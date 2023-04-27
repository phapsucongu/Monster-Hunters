#ifndef menu_h_
#define menu_h_
static int e_dame=1;
void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor);
void draw_time(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, Uint32 frametime);
void draw_score(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, int score);
#endif menu_h_h;
