#ifndef MOVEINTEGRITY_H
#define MOVEINTEGRITY_H
#include "Includes.h"
#include "Piece.h"

class MoveIntegrity {


    Piece Board[64];
    int getPieceColor(Vector2 pos);
    void MakeMove(Vector2 FirstPos , Vector2 SecondPos);
    bool Check_Pawn(int color ,Vector2 FirstPos, Vector2 SecondPos);
    void InitializeBoard();


public:
    bool CheckMove(Vector2 FirstPos, Vector2 SecondPos);
    std::array<int, 64> GetBoard();

    MoveIntegrity();
    ~MoveIntegrity();
};

#endif