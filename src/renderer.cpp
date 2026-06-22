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
    //Loads all the needed textures
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
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        Empty, Empty, Empty, Empty, Empty, Empty, Empty, Empty,
        White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,White_Pawn,
        White_Rook, White_Horse, White_Bishop, White_Queen,White_King, White_Bishop, White_Horse, White_Rook
    };
}

void renderer::DrawPieces()
{
    float posy ;
    float posx ;
    float SpriteOff;
    float SelectedPieceOffset = 0;

    int CurrPiece;
    Texture CurrTexture = wPiecesTex;
    Texture SelectedPieceTex = wPiecesTex;

    for (int y = 0 ; y < 8 ; y++) {
        for (int x = 0; x < 8 ; x++){
            posy = y * TileSize;
            posx = x * TileSize;
            SpriteOff = 0;

            CurrPiece = Board[y][x];
            CurrTexture = wPiecesTex;

            if (CurrPiece == Empty) {
                continue;
            }
            //Check if the current piece is Black
            // Black pieces have a 1 in front to declare that they are black so subtracting 10 from them
            // Wont make them below 0
            if (CurrPiece - 10 >= 0) {
                CurrTexture = bPiecesTex;
                SpriteOff = PieceSize * (CurrPiece - 10);

            }
            //White piecees have a 0 in front to declare that they are white so subtracting 10 from them
            // Will make them below 0
            if (CurrPiece - 10 <0) {
                CurrTexture = wPiecesTex;
                SpriteOff = PieceSize * (CurrPiece);

            }
            //Check whether the loop is on a selected piece
            //if so we save the offset and texture to render later so that selected pieces are always on top
            if (CurrPiece == SelectedPiece && FirstPosition.x == x && FirstPosition.y == y) {
                SelectedPieceOffset = SpriteOff;
                SelectedPieceTex = CurrTexture;
                continue;

            }

            DrawTexturePro(CurrTexture,{SpriteOff, 0, PieceSize, PieceSize},{Offset + posx + 5 , Offset + posy + 5, PieceSize, PieceSize},{0, 0},0.0f,WHITE);
        }

    }
    if (PieceSelected) {
        posx = GetMouseX();
        posy = GetMouseY();
        DrawTexturePro(SelectedPieceTex,{SelectedPieceOffset, 0, PieceSize, PieceSize},{posx -35 , posy -35 , PieceSize, PieceSize},{0, 0},0.0f,WHITE);
    }

}

void renderer::DrawCursor(float x , float y)
{
    //return if out of bounds
    if (x < 0 || y < 0) {
        return;
    }
    DrawTexturePro(CursorTex , {0 , 0 , 32 , 32} ,{x , y , 32 , 32}, {0 , 0} , 0.0f , WHITE);
}
int renderer::getPieceColor(Vector2 pos)
{
    if (Board[pos.y][pos.x] - 10 < 0) {
        return White;
    }
    if (Board[pos.y][pos.x] - 10 >= 0) {
        return Black;
    }

}
void renderer::UpdateBoard()
{
    MoveIntegrity Integrity;

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !PieceSelected) {
        PieceSelected = true;
        FirstPosition.x = (GetMouseX() - Offset) / TileSize;
        FirstPosition.y = (GetMouseY() -Offset) / TileSize;
        SelectedPiece =  Board[FirstPosition.y][FirstPosition.x];
        // std::cout<<"First Position"<<std::endl;
        //std::cout<<"X: "<<FirstPosition.x + 1<<"Y: "<<FirstPosition.y + 1<<std::endl;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && PieceSelected){
        PieceSelected = false;
        SelectedPiece = 6;
        SecondPosition.x =(GetMouseX() - Offset) / TileSize;
        SecondPosition.y =(GetMouseY() - Offset) / TileSize;
        //std::cout<<"Second Position"<<std::endl;
        //std::cout<<"X: "<<SecondPosition.x + 1<<"Y: "<<SecondPosition.y + 1<<std::endl;


        //std::cout<<"Piece 1: "<<Board[FirstPosition.x][FirstPosition.y]<<std::endl;
        //std::cout<<"Piece 2: "<<Board[SecondPosition.x][SecondPosition.y]<<std::endl;
        if (FirstPosition.x == SecondPosition.x && FirstPosition.y == SecondPosition.y) {
            return;
        }

       bool MoveAccepted = Integrity.CheckMove( Board[FirstPosition.y][FirstPosition.x],getPieceColor(FirstPosition), FirstPosition , SecondPosition , Board);

        if (MoveAccepted) {
            Board[SecondPosition.y][SecondPosition.x] =
    Board[FirstPosition.y][FirstPosition.x];
            Board[FirstPosition.y][FirstPosition.x] = 6;;
        }





    }
}

void renderer::render()
{
    DrawTexture(BoardTex , 0 , 0 , WHITE);
    DrawPieces();
    DrawCursor(GetMouseX() , GetMouseY());
    UpdateBoard();
}

