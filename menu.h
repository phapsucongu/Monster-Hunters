#ifndef menu_h_
#define menu_h_
void run_menu(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor);
void draw_time(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, Uint32 frametime);
void draw_score(SDL_Renderer* renderer,TTF_Font* font,SDL_Color textColor, int score);
class dame
{
public:
    static int e_dame;
};
#endif menu_h_h;
