#ifndef MOVEINTEGRITY_H
#define MOVEINTEGRITY_H
#include "Includes.h"
#include "Piece.h"

class MoveIntegrity {

    bool Answer = true;

    Piece Board[64];
    int getPieceColor(Vector2 pos);

    bool Check_Pawn(int color, Vector2 FirstPos, Vector2 SecondPos);
    void InitializeBoard();


public:
    bool CheckMove(int id, int color, Vector2 FirstPos, Vector2 SecondPos);
    std::array<int, 64> GetBoard();

    MoveIntegrity();
    ~MoveIntegrity();
};

#endif