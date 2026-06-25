#ifndef MOVEINTEGRITY_H
#define MOVEINTEGRITY_H
#include "Includes.h"
#include "Piece.h"

class MoveIntegrity {


    Piece Board[64];
    int GetTile(Vector2 Pos);
    void MakeMove(Vector2 FirstPos , Vector2 SecondPos);
    bool Check_Rook(Vector2 FirstPos, Vector2 SecondPos);
    bool Check_Pawn(Vector2 FirstPos, Vector2 SecondPos);
    void InitializeBoard();


public:
    bool CheckMove(Vector2 FirstPos, Vector2 SecondPos);
    std::array<int, 64> GetBoard();

    MoveIntegrity();
    ~MoveIntegrity();
};

#endif