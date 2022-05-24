#include"TextObject.h"
TextObject::TextObject()
    {
        sur=NULL;
        texture=NULL;
        text_color.r=255;
        text_color.g=255;
        text_color.b=255;
    }

TextObject::~TextObject()
    {
        SDL_FreeSurface(sur);
        SDL_DestroyTexture(texture);
    }

void TextObject::set_font(const char* file)
    {
        font=TTF_OpenFont(file,80);
    }
void TextObject::setcolor(SDL_Color color)
    {
        text_color=color;
    }
void TextObject:: set_text(std::string Text)
    {
        text=Text;
    }
void TextObject::set_pos(SDL_Rect rect)
    {
        pos=rect;
    }
void TextObject::createText(SDL_Renderer* renderer)
    {
        sur = TTF_RenderText_Solid(font,text.c_str(),text_color);
        texture = SDL_CreateTextureFromSurface(renderer,sur);
    }
void TextObject::draw(SDL_Renderer* renderer)
    {
      SDL_RenderCopy(renderer, texture, NULL, &pos);
    }
