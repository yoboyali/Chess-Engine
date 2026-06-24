#include "MoveIntegrity.h"

bool MoveIntegrity::Check_Pawn(int color, Vector2 FirstPos, Vector2 SecondPos)
{
    int steps = 1;
    if (FirstPos.y == 1 || FirstPos.y == 6) { steps = 2; }

    if (FirstPos.y - SecondPos.y == steps * color || FirstPos.y - SecondPos.y == 1 * color) {
        return true;
    }
    return false;
}

void MoveIntegrity::InitializeBoard()
{
    const int backRank[8] = { 2, 1, 3, 4, 5, 3, 1, 2};

    for (int col = 0; col < 8; col++) {
        // Black back rank (row 0)
        Board[0 * 8 + col].id    = 10 + backRank[col];
        Board[0 * 8 + col].color = Black;

        // Black pawns (row 1)
        Board[1 * 8 + col].id    = 10 + 6;
        Board[1 * 8 + col].color = Black;

        // Empty rows 2-5
        for (int row = 2; row <= 5; row++) {
            Board[row * 8 + col].id    = Empty;
            Board[row * 8 + col].color = 0;
        }

        // White pawns (row 6)
        Board[6 * 8 + col].id    = 6;
        Board[6 * 8 + col].color = White;

        // White back rank (row 7)
        Board[7 * 8 + col].id    = backRank[col];
        Board[7 * 8 + col].color = White;
    }
}

bool MoveIntegrity::CheckMove(int id, int color, Vector2 FirstPos, Vector2 SecondPos)
{
    // TODO: route to per-piece check functions (Check_Pawn, etc.)
    return Answer;
}

std::array<int, 64> MoveIntegrity::GetBoard()
{
    std::array<int, 64> snapshot;
    for (int i = 0; i < 64; i++) {
        snapshot[i] = Board[i].id;
    }
    return snapshot;
}

MoveIntegrity::MoveIntegrity()
{
    InitializeBoard();
}

MoveIntegrity::~MoveIntegrity()
{
}