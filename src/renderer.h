//
// Created by Ali Hamdy on 22/06/2026.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "Includes.h"
#include "MoveIntegrity.h"

class renderer {


    bool PieceSelected = false;

    Texture BoardTex;
    Texture bPiecesTex;
    Texture wPiecesTex;
    Texture CursorTex;

    std::array<std::array<int, 8>, 8>Board;

    Vector2 FirstPosition;
    Vector2 SecondPosition;

    int numClicks = 1;
    int SelectedPiece;


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



    void LoadTextures();
    void ResetBoard();
    void DrawPieces();
    void DrawCursor(float x , float y);
    void UpdateBoard();
    int getPieceColor(Vector2 pos);

public:
    renderer();
    ~renderer();
    void render();

};



#endif //RENDERER_H
