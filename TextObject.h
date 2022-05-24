#include"SDL_ttf.h"
#include<string>
struct TextObject{
    TTF_Font* font;
    SDL_Surface* sur;
    SDL_Texture* texture;
    std::string text;
    SDL_Color text_color;

    SDL_Rect pos;
    TextObject();
    ~TextObject();

    void set_font(const char* file);
    void setcolor(SDL_Color color);
    void set_text(std::string Text);
    void set_pos(SDL_Rect rect);
    void createText(SDL_Renderer* renderer);
    void draw(SDL_Renderer* renderer);
};
