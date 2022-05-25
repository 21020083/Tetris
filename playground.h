#include"ScoreBoard.h"

struct playground{
    SDL_Color cellstate[20][10];
    void init();
    void draw(SDL_Renderer* renderer);
    void lock(Shape s,SDL_Renderer* renderer);
    bool canMove(Shape s);
    bool checkRows();
    bool checkGameEnd(Shape s);
    };
