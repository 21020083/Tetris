#include"shape.h"
#include"TextObject.h"
struct ScoreBoard
{

    TextObject gameScore,Line,Next_Piece;
    Shape next_piece;
    void create(SDL_Renderer* renderer);
    void show(SDL_Renderer* renderer );
    void update();
};
