#include <iostream>
#include "raylib.h"
#include <array>
const int WindowWidth = 710;
const int WindowHeight = 710;
const int Offset = 30;
const int TileSize = 80;
const int PieceSize = 80;
bool PieceSelected = false;
Texture BoardTex;
Texture bPiecesTex;
Texture wPiecesTex;
Texture CursorTex;

std::array<std::array<int, 8>, 8>Board;

Vector2 FirstPosition;
Vector2 SecondPosition;

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
void initializeTextures()
{
    BoardTex = LoadTexture("Texture/board.png");
    bPiecesTex = LoadTexture("Texture/bPieces.png");
    wPiecesTex = LoadTexture("Texture/wPieces.png");
    CursorTex = LoadTexture("Texture/cursor.png");

}
void resetBoard()
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
void DrawPieces()
{

    for (int y = 0 ; y < 8 ; y++) {
        for (int x = 0; x < 8 ; x++){
         float posy = y * TileSize;
         float posx = x * TileSize;
         Texture CurrTexture;
         float SpriteOff;

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
void DrawCursor(float x , float y)
{
    if (x < 0 || y < 0) {
        return;
    }
    DrawTexturePro(CursorTex , {0 , 0 , 16 , 16} ,{x , y , 16 , 16}, {0 , 0} , 0.0f , WHITE);
}

void UpdateBoard()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !PieceSelected) {
        PieceSelected = true;
        FirstPosition.x = (GetMouseX() - Offset) / TileSize;
        FirstPosition.y = (GetMouseY() -Offset) / TileSize;
        std::cout<<"First Position"<<std::endl;
        std::cout<<"X: "<<FirstPosition.x + 1<<"Y: "<<FirstPosition.y + 1<<std::endl;
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
int main()
{
    InitWindow(WindowWidth , WindowHeight , "Chess");
    initializeTextures();
    resetBoard();
    while (!WindowShouldClose()) {
        BeginDrawing();
        HideCursor();
        ClearBackground(WHITE);
        DrawTexture(BoardTex , 0 , 0 , WHITE);
        DrawPieces();
        DrawCursor(GetMouseX() , GetMouseY());
        UpdateBoard();
        EndDrawing();
    }
    UnloadTexture(BoardTex);
    CloseWindow();
    return 0;
}