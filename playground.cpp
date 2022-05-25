#include"playground.h"
SDL_Color BLACK{50,50,50};
    void playground::init(){
        for(int i=0;i<20;i++)
            for(int j=0;j<10;j++)
                cellstate[i][j]=BLACK;
    }
    void playground::draw(SDL_Renderer *renderer){
        for(int i=0;i<20;i++){
            for(int j=0;j<10;j++){
                SDL_Rect rect{j*block_size,i*block_size,block_size,block_size};
                SDL_SetRenderDrawColor(renderer,cellstate[i][j].r,cellstate[i][j].g,cellstate[i][j].b,255);
                SDL_RenderFillRect(renderer,&rect);
                SDL_SetRenderDrawColor(renderer,20,20,20,255);
                SDL_RenderDrawRect(renderer,&rect);

            }
        }

    };
    void playground::lock(Shape s,SDL_Renderer* renderer){
           for(int i=0;i<4;i++){
                int dx=s.pos[i]%4;
                int dy=s.pos[i]/4;
                cellstate[(s.y+dy*block_size)/block_size][(s.x+dx*block_size)/block_size]=s.color;
                }
        }
    bool playground::canMove(Shape s){
        for(int i=0;i<4;i++){
                int dx=s.pos[i]%4;
                int dy=s.pos[i]/4;
                SDL_Color c=cellstate[(s.y+dy*block_size)/block_size][(s.x+dx*block_size)/block_size];
                if(c.r !=BLACK.r || c.g !=BLACK.g || c.b !=BLACK.g)
                    return false;
                }
            return true;
        };

    bool playground::checkRows(){
    int count = 0;
    bool check=false;
    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++){
                if(cellstate[i][j].r !=BLACK.r || cellstate[i][j].g !=BLACK.g || cellstate[i][j].b !=BLACK.b)
                    count++;
        }
        if(count==10){
            for(int j=0;j<10;j++){
               for(int k=i-1;k>=0;k--){
                SDL_Color tmp=cellstate[k+1][j];
                cellstate[k+1][j]=cellstate[k][j];
                cellstate[k][j]=tmp;
               }
            }
            for(int j=0;j<10;j++)
                cellstate[0][j]=BLACK;

            check=true;
        }
        count=0;
    }
    return check;
}
    bool playground::checkGameEnd(Shape s)
{
    if(!canMove(s) &&  s.y == 0){
        return true;
    }
        return false;
}
