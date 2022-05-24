#include"shape.h"

void Shape::draw(SDL_Renderer* renderer)
    {
        for(int i=0;i<4;i++){
            int dx=pos[i]%4;
            int dy=pos[i]/4;
            SDL_Rect rect{x+dx*block_size,y+dy*block_size,block_size,block_size};
            SDL_SetRenderDrawColor(renderer, color.r,color.g, color.b,color.a);
            SDL_RenderFillRect(renderer, &rect);
            SDL_SetRenderDrawColor(renderer, color.r,color.g, color.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
            }
        }
void Shape::rotate(){
        int px=pos[1]%4;
        int py=pos[1]/4;
        if(pos[3]==13 || pos[7]==3){
            pos[0]=(pos[3]== 13 ? 4 : 1);
            pos[2]=(pos[3]== 13 ? 6 : 9);
            pos[3]=(pos[3]== 13 ? 7 : 13);
        }
        else{
            for(int i=0;i<4;i++){
                int dx=pos[i]%4;
                int dy=pos[i]/4;
                int x1=px+py-dy;
                int y1=py-px+dx;
                pos[i]=4*y1+x1;
            }
        }
    }

