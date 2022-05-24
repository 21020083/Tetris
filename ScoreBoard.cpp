#include"ScoreBoard.h"
#include<string>
#include<iostream>


    void ScoreBoard::show(SDL_Renderer* renderer )
    {
            gameScore.draw(renderer);
            Line.draw(renderer);
            Next_Piece.draw(renderer);

            next_piece.x=420;
            next_piece.y=400;
            next_piece.draw(renderer);
    }
