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
    int Destination = GetTile(SecondPos);
    int OriginalTile = GetTile(FirstPos);

    Board[Destination] = Board[OriginalTile];
    Board[OriginalTile].id = Empty;
    Board[OriginalTile].color = 0;
}

bool MoveIntegrity::Check_Bishop(Vector2 FirstPos, Vector2 SecondPos)
{
    int DestinationTile = GetTile(SecondPos);
    std::vector<int> LegalMoves = {};

    int row = FirstPos.x;
    int column = FirstPos.y;
    bool stopTopLeft = false, stopTopRight = false;
    bool stopBottomLeft = false, stopBottomRight = false;

    for (int Index = 1; Index < 8; Index++) {
        //  Top Left
        if (!stopTopLeft) {
            int TopLeft = GetTile({(float)row - Index, (float)(column + Index)});
            if (TopLeft != -1) {
                LegalMoves.push_back(TopLeft);
                if (Board[TopLeft].id != Empty) stopTopLeft = true;
            } else stopTopLeft = true;
        }

        //  Top Right
        if (!stopTopRight) {
            int TopRight = GetTile({(float)row + Index, (float)(column + Index)});
            if (TopRight != -1) {
                LegalMoves.push_back(TopRight);
                if (Board[TopRight].id != Empty) stopTopRight = true;
            } else stopTopRight = true;
        }

        //  Bottom Left
        if (!stopBottomLeft) {
            int BottomLeft = GetTile({(float)(row - Index), (float)column - Index});
            if (BottomLeft != -1) {
                LegalMoves.push_back(BottomLeft);
                if (Board[BottomLeft].id != Empty) stopBottomLeft = true;
            } else stopBottomLeft = true;
        }

        //  Bottom Right
        if (!stopBottomRight) {
            int BottomRight = GetTile({(float)(row + Index), (float)column - Index});
            if (BottomRight != -1) {
                LegalMoves.push_back(BottomRight);
                if (Board[BottomRight].id != Empty) stopBottomRight = true;
            } else stopBottomRight = true;
        }
    }
    for (int tile : LegalMoves) {
        if (tile == DestinationTile) return true;
    }
    return false;
}

bool MoveIntegrity::Check_Rook(Vector2 FirstPos, Vector2 SecondPos)
{
    int DestinationTile = GetTile(SecondPos);
    std::vector<int> LegalMoves = {};

    int row = FirstPos.x;
    int column = FirstPos.y;
    bool stopUpCheck = false, stopDownCheck = false;
    bool stopLeftCheck = false, stopRightCheck = false;

    for (int Index = 1; Index < 8; Index++) {
        //  UP
        if (!stopUpCheck) {
            int UpTile = GetTile({FirstPos.x, (float)(column + Index)});
            if (UpTile != -1) {
                LegalMoves.push_back(UpTile);
                if (Board[UpTile].id != Empty) stopUpCheck = true;
            } else stopUpCheck = true;
        }

        //  DOWN
        if (!stopDownCheck) {
            int DownTile = GetTile({FirstPos.x, (float)(column - Index)});
            if (DownTile != -1) {
                LegalMoves.push_back(DownTile);
                if (Board[DownTile].id != Empty) stopDownCheck = true;
            } else stopDownCheck = true;
        }

        //  LEFT
        if (!stopLeftCheck) {
            int LeftTile = GetTile({(float)(row - Index), FirstPos.y});
            if (LeftTile != -1) {
                LegalMoves.push_back(LeftTile);
                if (Board[LeftTile].id != Empty) stopLeftCheck = true;
            } else stopLeftCheck = true;
        }

        //  RIGHT
        if (!stopRightCheck) {
            int RightTile = GetTile({(float)(row + Index), FirstPos.y});
            if (RightTile != -1) {
                LegalMoves.push_back(RightTile);
                if (Board[RightTile].id != Empty) stopRightCheck = true;
            } else stopRightCheck = true;
        }
    }
    for (int tile : LegalMoves) {
        if (tile == DestinationTile) return true;
    }
    return false;
}

bool MoveIntegrity::Check_Knight(Vector2 FirstPos, Vector2 SecondPos)
{
    int DistanceX = abs(FirstPos.x - SecondPos.x);
    int DistanceY = abs(FirstPos.y - SecondPos.y);

    if ( DistanceX == 2 && DistanceY == 1||
         DistanceX == 1 && DistanceY == 2) {
        return true;
    }


    return false;
}

bool MoveIntegrity::Check_Pawn(Vector2 FirstPos, Vector2 SecondPos)
{
    // Todo enn passant + promotion
    int OriginalTile = GetTile(FirstPos);
    int DestinationTile = GetTile(SecondPos);
    int fx = (int)FirstPos.x;
    int fy = (int)FirstPos.y;
    int color = Board[OriginalTile].color;


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

    for (int i = 0 ; i < LegalMoves.size() ; i++) {
        if (LegalMoves[i] == SecondPos) {return true;}
    }

    return false;
}

void MoveIntegrity::InitializeBoard()
{
    const int backRank[8] = { White_Rook, White_Horse, White_Bishop, White_Queen, White_King, White_Bishop, White_Horse, White_Rook};

    for (int col = 0; col < 8; col++) {
        // Black back rank (row 0)
        Board[0 * 8 + col].id    = 10 + backRank[col];
        Board[0 * 8 + col].color = Black;

        // Black pawns (row 1)
        Board[1 * 8 + col].id    = 10 + White_Pawn;
        Board[1 * 8 + col].color = Black;
        Board[1 * 8 + col].startingTile = 1 * 8 + col;

        // Empty rows 2-5
        for (int row = 2; row <= 5; row++) {
            Board[row  * 8 + col].id    = Empty;
            Board[row * 8 + col].color = 0;
        }

        // White pawns (row 6)
        Board[6 * 8 + col].id    = White_Pawn;
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

        case White_Rook:
        case Black_Rook:
            Answer = Check_Rook(FirstPos , SecondPos);
            break;
        case White_Horse:
        case Black_Horse:
            Answer = Check_Knight(FirstPos , SecondPos);
            break;
        case White_Bishop:
        case Black_Bishop:
            Answer = Check_Bishop(FirstPos , SecondPos);
            break;
        case White_Pawn:
        case Black_Pawn:
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