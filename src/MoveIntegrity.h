//
// Created by Ali Hamdy on 22/06/2026.
//

#ifndef MOVEINTEGRITY_H
#define MOVEINTEGRITY_H
#include "Includes.h"


class MoveIntegrity {

    bool Answer = true;
    struct Piece
    {
        int id ;
        int color;

    };

    enum pieces
    {
        White_Pawn   = 00,
        White_Horse  = 01,
        White_Rook   = 02,
        White_Bishop = 03,
        White_Queen  = 04,
        White_King   = 05,


        Black_Pawn   = 10,
        Black_Horse  = 11,
        Black_Rook   = 12,
        Black_Bishop = 13,
        Black_Queen  = 14,
        Black_King   = 15,

    };

    int getPieceColor(Vector2 pos , std::array<std::array<int, 8>, 8> Board);
    bool Check_Pawn(int color ,  Vector2 FirstPos , Vector2 SecondPos);

public:
    bool CheckMove(int id , int color , Vector2 FirstPos , Vector2 SecondPos ,  std::array<std::array<int, 8>, 8>Board);
    MoveIntegrity();
    ~MoveIntegrity();

};



#endif //MOVEINTEGRITY_H
