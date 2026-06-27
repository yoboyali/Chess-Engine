#include "renderer.h"

MoveIntegrity Integrity;

renderer::renderer()
{
    LoadTextures();
    BoardSnapshot = Integrity.GetBoard();
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
    BoardTex   = LoadTexture("Texture/board.png");
    bPiecesTex = LoadTexture("Texture/bPieces.png");
    wPiecesTex = LoadTexture("Texture/wPieces.png");
    CursorTex  = LoadTexture("Texture/cursor.png");
}

void renderer::DrawPieces()
{
    float posy;
    float posx;
    float SpriteOff;
    float SelectedPieceOffset = 0;

    int CurrPiece;
    Texture CurrTexture      = wPiecesTex;
    Texture SelectedPieceTex = wPiecesTex;

    BoardSnapshot = Integrity.GetBoard();


    for (int y = 0; y < 8; y++) {
        posy = y * TileSize;

        for (int x = 0; x < 8; x++) {
            posx = x * TileSize;

            CurrPiece   = BoardSnapshot[y * 8 + x];
            CurrTexture = wPiecesTex;

            if (CurrPiece == Empty) {
                continue;
            }

            if (CurrPiece - 10 >= 0) {
                CurrTexture = bPiecesTex;
                SpriteOff   = PieceSize * (CurrPiece - 10);
            }

            if (CurrPiece - 10 < 0) {
                CurrTexture = wPiecesTex;
                SpriteOff   = PieceSize * CurrPiece;
            }

            if (CurrPiece == SelectedPiece && FirstPosition.x == x && FirstPosition.y == y) {
                SelectedPieceOffset = SpriteOff;
                SelectedPieceTex    = CurrTexture;
                continue;
            }

            DrawTexturePro(CurrTexture,
                           {SpriteOff, 0, PieceSize, PieceSize},
                           {Offset + posx + 5, Offset + posy + 5, PieceSize, PieceSize},
                           {0, 0}, 0.0f, WHITE);
        }
    }

    if (PieceSelected) {
        posx = GetMouseX();
        posy = GetMouseY();
        DrawTexturePro(SelectedPieceTex,
                       {SelectedPieceOffset, 0, PieceSize, PieceSize},
                       {posx - 35, posy - 35, PieceSize, PieceSize},
                       {0, 0}, 0.0f, WHITE);
    }
    for (int i = 0 ; i < moves.size() ; i++) {
        int temp = moves[i];
        Vector2 pos = {(float)(temp / 8), (float)(temp % 8)};
        DrawCircle(pos.x * TileSize - 35 , pos.y  * TileSize - 35, 5 , RED);
    }
}

void renderer::DrawCursor(float x, float y)
{
    if (x < 0 || y < 0) { return; }
    DrawTexturePro(CursorTex, {0, 0, 32, 32}, {x, y, 32, 32}, {0, 0}, 0.0f, WHITE);
}

void renderer::UpdateBoard()
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        int x = (GetMouseX() - Offset) / TileSize;
        int y = (GetMouseY() - Offset) / TileSize;
        int Tile = y * 8 + x;
        if (BoardSnapshot[Tile] == 13 || BoardSnapshot[Tile] == 3) {
            moves = Integrity.getBishopMoves();
        }
    }
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !PieceSelected) {
        int x = (GetMouseX() - Offset) / TileSize;
        int y = (GetMouseY() - Offset) / TileSize;

        if (BoardSnapshot[y * 8 + x] == Empty) { return; }


        PieceSelected    = true;
        FirstPosition.x  = x;
        FirstPosition.y  = y;
        SelectedPiece    = BoardSnapshot[FirstPosition.y * 8 + FirstPosition.x];
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && PieceSelected) {
        PieceSelected = false;

        SecondPosition.x = (GetMouseX() - Offset) / TileSize;
        SecondPosition.y = (GetMouseY() - Offset) / TileSize;

        SelectedPiece = Empty;

        if (FirstPosition.x == SecondPosition.x && FirstPosition.y == SecondPosition.y) {
            return;
        }

        bool MoveAccepted = Integrity.CheckMove(FirstPosition,SecondPosition , true);

        if (MoveAccepted) {
            BoardSnapshot[SecondPosition.y * 8 + SecondPosition.x] =
                BoardSnapshot[FirstPosition.y * 8 + FirstPosition.x];
            BoardSnapshot[FirstPosition.y * 8 + FirstPosition.x] = Empty;
        }
    }
}

void renderer::render()
{
    DrawTexture(BoardTex, 0, 0, WHITE);
    DrawPieces();
    DrawCursor(GetMouseX(), GetMouseY());
    UpdateBoard();
}