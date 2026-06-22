//
// Created by Ali Hamdy on 22/06/2026.
//

#include "renderer.h"

renderer::renderer()
{
    LoadTextures();
    ResetBoard();
}

renderer::~renderer()
{
    UnloadTexture(BoardTex);
    UnloadTexture(wPiecesTex);
    UnloadTexture(bPiecesTex);
    UnloadTexture(CursorTex);
}

void renderer::LoadTextures()
{
    BoardTex = LoadTexture("Texture/board.png");
    bPiecesTex = LoadTexture("Texture/bPieces.png");
    wPiecesTex = LoadTexture("Texture/wPieces.png");
    CursorTex = LoadTexture("Texture/cursor.png");

}

void renderer::ResetBoard()
{
    Board = {
        Black_Rook, Black_Horse, Black_Bishop, Black_Queen,Black_King, Black_Bishop, Black_Horse, Black_Rook,
        Black_Pawn,Black_Pawn,Black_Pawn,Black_Pawn,Black_Pawn,Black_Pawn,Black_Pawn,Black_Pawn,
        6,6,6,6,6,6,6,6,
        6,6,6,6,6,6,6,6,
        6,6,6,6,6,6,6,6,
        6,6,6,6,6,6,6,6,
        White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,
        White_Rook, White_Horse, White_Bishop, White_Queen,White_King, White_Bishop, White_Horse, White_Rook
    };
}

void renderer::DrawPieces()
{

    for (int y = 0 ; y < 8 ; y++) {
        for (int x = 0; x < 8 ; x++){
            float posy = y * TileSize;
            float posx = x * TileSize;
            Texture CurrTexture = wPiecesTex;
            float SpriteOff = 0;

            if (Board[y][x] == 6) {
                continue;
            }
            if (Board[y][x] - 10 >= 0) {
                CurrTexture = bPiecesTex;
                SpriteOff = PieceSize * (Board[y][x] - 10);

            }
            if (Board[y][x] - 10 <0) {
                CurrTexture = wPiecesTex;
                SpriteOff = PieceSize * (Board[y][x]);

            }


            DrawTexturePro(CurrTexture,{SpriteOff, 0, PieceSize, PieceSize},{Offset + posx + 5 , Offset + posy + 5, PieceSize, PieceSize},{0, 0},0.0f,WHITE);


        }

    }
}

void renderer::DrawCursor(float x , float y)
{
    if (x < 0 || y < 0) {
        return;
    }
    DrawTexturePro(CursorTex , {0 , 0 , 16 , 16} ,{x , y , 16 , 16}, {0 , 0} , 0.0f , WHITE);
}

void renderer::UpdateBoard()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !PieceSelected) {
        PieceSelected = true;
        FirstPosition.x = (GetMouseX() - Offset) / TileSize;
        FirstPosition.y = (GetMouseY() -Offset) / TileSize;
        // std::cout<<"First Position"<<std::endl;
        //std::cout<<"X: "<<FirstPosition.x + 1<<"Y: "<<FirstPosition.y + 1<<std::endl;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && PieceSelected){
        PieceSelected = false;
        SecondPosition.x =(GetMouseX() - Offset) / TileSize;
        SecondPosition.y =(GetMouseY() - Offset) / TileSize;
        //std::cout<<"Second Position"<<std::endl;
        //std::cout<<"X: "<<SecondPosition.x + 1<<"Y: "<<SecondPosition.y + 1<<std::endl;


        //std::cout<<"Piece 1: "<<Board[FirstPosition.x][FirstPosition.y]<<std::endl;
        //std::cout<<"Piece 2: "<<Board[SecondPosition.x][SecondPosition.y]<<std::endl;
        if (FirstPosition.x == SecondPosition.x && FirstPosition.y == SecondPosition.y) {
            return;
        }
        Board[SecondPosition.y][SecondPosition.x] =
            Board[FirstPosition.y][FirstPosition.x];

        Board[FirstPosition.y][FirstPosition.x] = 6;;




    }
}

void renderer::render()
{
    DrawTexture(BoardTex , 0 , 0 , WHITE);
    DrawPieces();
    DrawCursor(GetMouseX() , GetMouseY());
    UpdateBoard();
}

