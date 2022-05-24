#include <SDL.h>
#include<cstdlib>
#include<ctime>
#define block_size 32
struct Shape
{

    SDL_Color color;
    int pos[4];
    int x,y;
    int size;

    void draw(SDL_Renderer* renderer);
    void rotate();
    void spawn();
}
;

