#include "MoveIntegrity.h"


bool operator==(Vector2 a , Vector2 b)
{
    return (a.x == b.x && a.y == b.y);
}

int MoveIntegrity::GetTile(Vector2 Pos)
{
    return Pos.y * 8 + Pos.x;
}

void MoveIntegrity::MakeMove(Vector2 FirstPos, Vector2 SecondPos)
{
    int DesintationTile = GetTile(SecondPos);
    int OriginalTile = GetTile(FirstPos);

    Board[DesintationTile] = Board[OriginalTile];
    Board[OriginalTile].id = Empty;
    Board[OriginalTile].color = 0;
}

bool MoveIntegrity::Check_Rook(Vector2 FirstPos, Vector2 SecondPos)
{
    int Tile = GetTile(FirstPos);
    int color = Board[Tile].color;
    bool Answer = false;
    std::array<Vector2 , 14 >LegalMoves = {};

    int Index = 0;
    for (int column = 0 ; column < 8 ; column++) {
        int CurentTile = GetTile({(float)column , FirstPos.x});

        if (CurentTile == Tile){continue;}
            LegalMoves[Index] = {FirstPos.x ,(float)column};
            Index++;
        //if (Board[column * 8 + (int)FirstPos.x].color == Black) {break;}
    }

    /*for (int row = 0 ; row < 8 ; row++) {
        if (FirstPos.y * 8 + row == Tile){continue;}
            LegalMoves[Index] = {(float)row ,FirstPos.y};
            Index++;
        //if (Board[(int)FirstPos.y * 8 + row].id != Empty){break;}
    }*/
    std::cout<<"Legal moves: "<<std::endl;
    for (int i = 0 ; i < LegalMoves.size() ; i++) {
        std::cout<<"X: "<<LegalMoves[i].x<<" Y: "<<LegalMoves[i].y<<std::endl;
    }
    for (int i = 0 ; i < LegalMoves.size() ; i++) {
        if (LegalMoves[i] == SecondPos) {Answer = true;}
    }

    return Answer;
}

bool MoveIntegrity::Check_Pawn(Vector2 FirstPos, Vector2 SecondPos)
{
    // Todo enn passant + promotion
    int OriginalTile = GetTile(FirstPos);
    int DestinationTile = GetTile(SecondPos);
    int fx = (int)FirstPos.x;
    int fy = (int)FirstPos.y;
    int color = Board[OriginalTile].color;

    bool answer = false;

    auto pieceAt = [&](int x, int y) {
        return Board[y * 8 + x].id;
    };

    std::array<Vector2 , 4> LegalMoves;
    LegalMoves[0] = {FirstPos.x , FirstPos.y - 1 * color};
    LegalMoves[1] = {FirstPos.x -1 , FirstPos.y - 1 * color};
    LegalMoves[2] = {FirstPos.x +1 , FirstPos.y - 1 * color};
    LegalMoves[3] = {FirstPos.x , FirstPos.y - 2 * color};

    if (OriginalTile != Board[OriginalTile].startingTile || Board[DestinationTile].id != 0) {LegalMoves[3] = {-1,-1};}
    if (pieceAt(fx, fy - color) != 0) {LegalMoves[0] = {-1, -1};LegalMoves[3] = {-1,-1};}
    if (pieceAt(fx - 1, fy - color) == 0) LegalMoves[1] = {-1, -1};
    if (pieceAt(fx + 1, fy - color) == 0) LegalMoves[2] = {-1, -1};

    //std::cout<<"Second pos X: "<<SecondPos.x<<" Second pos y: "<<SecondPos.y<<std::endl;
    for (int i = 0 ; i < LegalMoves.size() ; i++) {
        //std::cout<<"Allowed pos X: "<<AllowedMoves[i].x<<" Allowed pos Y: "<<AllowedMoves[i].y<<std::endl;
        if (LegalMoves[i] == SecondPos) {answer = true;}
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
        Board[1 * 8 + col].startingTile = 1 * 8 + col;

        // Empty rows 2-5
        for (int row = 2; row <= 5; row++) {
            Board[row  * 8 + col].id    = Empty;
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
    int OriginalTile = GetTile(FirstPos);
    int DestinationTile = GetTile(SecondPos);
    // TODO: route to per-piece check functions (Check_Pawn, etc.)

    //Check basic cases like friendly fire / invalid tile
    if (Board[OriginalTile].color == Board[DestinationTile].color ) {
        return false;
    }
    if (SecondPos.x < 0 || SecondPos.x > 7
        ||SecondPos.y < 0 || SecondPos.x >7){return false;}

    switch (Board[OriginalTile].id) {

        case 2:
        case 12:
            Answer = Check_Rook(FirstPos , SecondPos);
            break;
        case 6:
        case 16:
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