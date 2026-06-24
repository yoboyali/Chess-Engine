#include "MoveIntegrity.h"

void MoveIntegrity::MakeMove(Vector2 FirstPos, Vector2 SecondPos)
{
    Board[(int)SecondPos.y * 8 + (int)SecondPos.x] = Board[(int)FirstPos.y * 8 + (int)FirstPos.x];
    Board[(int)FirstPos.y * 8 + (int)FirstPos.x].id = Empty;
    Board[(int)FirstPos.y * 8 + (int)FirstPos.x].color = 0;
}

bool MoveIntegrity::Check_Pawn(Vector2 FirstPos, Vector2 SecondPos)
{
    int OriginalTile = (int)FirstPos.y * 8 + (int)FirstPos.y;
    int DestinationTile = (int)SecondPos.y * 8 + (int)SecondPos.y;


    bool answer = false;
    int color = 1;

    std::array<Vector2 , 4> AllowedMoves;
    AllowedMoves[0] = {FirstPos.x , FirstPos.y + 1};
    AllowedMoves[1] = {FirstPos.x -1 , FirstPos.y + 1};
    AllowedMoves[2] = {FirstPos.x +1 , FirstPos.y + 1};
    AllowedMoves[3] = {FirstPos.x , FirstPos.y + 2};

    if (OriginalTile != Board[OriginalTile].startingTile) {AllowedMoves[3] = {0,0};}

    if (Board[DestinationTile].id != 0) {
        for (int i = 0; i < AllowedMoves.size(); i++) {
            if (DestinationTile == AllowedMoves[i].y * 8 + AllowedMoves[i].x) {
                AllowedMoves[i] = {0,0};
            }
        }
    }

    




    return answer;
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
        Board[6 * 8 + col].startingTile = 6 * 8 + col ;

        // White back rank (row 7)
        Board[7 * 8 + col].id    = backRank[col];
        Board[7 * 8 + col].color = White;
    }
}

bool MoveIntegrity::CheckMove(Vector2 FirstPos, Vector2 SecondPos)
{
    bool Answer = false;
    // TODO: route to per-piece check functions (Check_Pawn, etc.)
    if (Board[(int)FirstPos.y * 8 + (int)FirstPos.x].color == Board[(int)SecondPos.y * 8 + (int)SecondPos.x].color ) {
        return false;
    }
    if (SecondPos.x < 0 || SecondPos.x > 7
        ||SecondPos.y < 0 || SecondPos.x >7){return false;}

    switch (Board[(int)FirstPos.y * 8 + (int)FirstPos.x].id) {
        case 6:
            Answer = Check_Pawn(FirstPos , SecondPos);
            break;
        default:
            break;
    }


    if (Answer == true){MakeMove(FirstPos , SecondPos);}
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