//
// Created by Ali Hamdy on 22/06/2026.
//

#include "MoveIntegrity.h"


int MoveIntegrity::getPieceColor(Vector2 pos , std::array<std::array<int, 8>, 8> Board)
{
    if (Board[pos.y][pos.x] == Empty) {
        return Empty;
    }
    if (Board[pos.y][pos.x] - 10 < 0) {
        return White;
    }
    if (Board[pos.y][pos.x] - 10 >= 0) {
        return Black;
    }


}

bool MoveIntegrity::Check_Pawn(int color , Vector2 FirstPos , Vector2 SecondPos)
{
    int steps =  1;
    if (FirstPos.y == 1 ||FirstPos.x == 6){steps = 2;}

    if (FirstPos.y - SecondPos.y <= steps * color && FirstPos.y - SecondPos.y <= 1 ) {
        return true;
    }

    return false;
}

bool MoveIntegrity::CheckMove(int id, int color, Vector2 FirstPos, Vector2 SecondPos,std::array<std::array<int, 8>, 8> Board)
{
    int TargetColor = getPieceColor(SecondPos , Board);
    if (color == TargetColor ) {
        Answer = false;
    }
    if (SecondPos.x < 0 || SecondPos.y < 0 || SecondPos.x > 7 || SecondPos.y > 7 ) {
        Answer = false;
    }

    switch (id) {
        case White_Pawn:
        case Black_Pawn:
            Answer = Check_Pawn(color , FirstPos , SecondPos);
            break;

    }




    return Answer;

}

MoveIntegrity::MoveIntegrity()
{
}

MoveIntegrity::~MoveIntegrity()
{
}
