
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

    std::array<int, 64> BoardSnapshot;

    Vector2 FirstPosition;
    Vector2 SecondPosition;

    int numClicks = 1;
    int SelectedPiece;

    void LoadTextures();
    void DrawPieces();
    void DrawCursor(float x , float y);
    void UpdateBoard();

public:
    renderer();
    ~renderer();
    void render();

};



#endif //RENDERER_H
