#ifndef MOVEINTEGRITY_H
#define MOVEINTEGRITY_H
#include "Includes.h"
#include "Piece.h"

class MoveIntegrity {


    Piece Board[64];
    int GetTile(Vector2 Pos);
    void MakeMove(Vector2 FirstPos , Vector2 SecondPos);
    bool Check_Bishop(Vector2 FirstPos , Vector2 SecondPos);
    bool Check_Rook(Vector2 FirstPos, Vector2 SecondPos);
    bool Check_Knight(Vector2 FirstPos , Vector2 SecondPos);
    bool Check_Queen(Vector2 FirstPos , Vector2 SecondPos);
    bool Check_Pawn(Vector2 FirstPos, Vector2 SecondPos);
    void InitializeBoard();

    enum pieces
    {
        White_Horse  = 1,
        White_Rook   = 2,
        White_Bishop = 3,
        White_Queen  = 4,
        White_King   = 5,
        White_Pawn   = 6,



        Black_Horse  = 11,
        Black_Rook   = 12,
        Black_Bishop = 13,
        Black_Queen  = 14,
        Black_King   = 15,
        Black_Pawn   = 16,


    };

public:
    bool CheckMove(Vector2 FirstPos, Vector2 SecondPos);
    std::array<int, 64> GetBoard();

    MoveIntegrity();
    ~MoveIntegrity();
};

#endif