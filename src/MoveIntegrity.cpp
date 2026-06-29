#include "MoveIntegrity.h"


bool operator==(Vector2 a , Vector2 b)
{
    return (a.x == b.x && a.y == b.y);
}

int MoveIntegrity::GetTile(Vector2 Pos)
{
    if (Pos.x > 7 || Pos.y > 7 || Pos.x < 0 || Pos.y < 0) return -1;
    return Pos.y * 8 + Pos.x;
}

void MoveIntegrity::MakeMove(Vector2 FirstPos, Vector2 SecondPos)
{
    int Destination = GetTile(SecondPos);
    int OriginalTile = GetTile(FirstPos);

    Board[Destination] = Board[OriginalTile];
    Board[Destination].Moved = true;

    Board[OriginalTile].id = Empty;
    Board[OriginalTile].color = 0;
    Board[OriginalTile].startingTile = -1;
    //Board[OriginalTile].Moved = true;

}

void MoveIntegrity::Castle(Vector2 KingPos, Vector2 SecondPos)
{
    std::vector<float>SquaresToCheckLeft  = {1.0 , 2.0, 3.0};
    std::vector<float>SquaresToCheckRight = {5.0 , 6.0};

    int King = GetTile(KingPos);
    int color = Board[King].color;
    int RookID = (color == Black) ? Black_Rook : White_Rook;

    //5 - 7 = -2 -> Right < 0
    //5 - 0 = 5 -> Left > 0
    int Direction = KingPos.x - SecondPos.x;
    float CastleDirection = LeftCastle;
    float x = 0.0;

    std::vector<float>SquaresToCheck = SquaresToCheckLeft;

    if (Direction < 0) {
        x = 7;
        CastleDirection = RightCastle;
        SquaresToCheck = SquaresToCheckRight;

    }

    Vector2 RookPos = { x , KingPos.y};
    int RookTile = GetTile(RookPos);

    for (int i = 0 ; i < SquaresToCheck.size() ; i++) {
        if (IsUnderAttack(color , {SquaresToCheck[i] , KingPos.y})) {
            return;
        }
}


    if (Board[RookTile].id == RookID && Board[RookTile].Moved == false && Board[King].Moved == false) {
        MakeMove(KingPos , SecondPos);
        MakeMove(RookPos , { CastleDirection, KingPos.y});
    }

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
                if (TopLeft < 0) LegalMoves.pop_back();
                if (Board[TopLeft].id != Empty) stopTopLeft = true;
            } else stopTopLeft = true;
        }

        //  Top Right
        if (!stopTopRight) {
            int TopRight = GetTile({(float)row + Index, (float)(column + Index)});
            if (TopRight != -1) {
                LegalMoves.push_back(TopRight);
                if (TopRight < 0) LegalMoves.pop_back();
                if (Board[TopRight].id != Empty) stopTopRight = true;
            } else stopTopRight = true;
        }

        //  Bottom Left
        if (!stopBottomLeft) {
            int BottomLeft = GetTile({(float)(row - Index), (float)column - Index});
            if (BottomLeft != -1) {
                LegalMoves.push_back(BottomLeft);
                if (BottomLeft < 0) LegalMoves.pop_back();
                if (Board[BottomLeft].id != Empty) stopBottomLeft = true;
            } else stopBottomLeft = true;
        }

        //  Bottom Right
        if (!stopBottomRight) {
            int BottomRight = GetTile({(float)(row + Index), (float)column - Index});
            if (BottomRight != -1) {
                LegalMoves.push_back(BottomRight);
                if (BottomRight < 0) LegalMoves.pop_back();
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
                if (UpTile < 0) LegalMoves.pop_back();

            } else stopUpCheck = true;
        }

        //  DOWN
        if (!stopDownCheck) {
            int DownTile = GetTile({FirstPos.x, (float)(column - Index)});
            if (DownTile != -1) {
                LegalMoves.push_back(DownTile);
                if (Board[DownTile].id != Empty) stopDownCheck = true;
                if (DownTile < 0) LegalMoves.pop_back();
            } else stopDownCheck = true;
        }

        //  LEFT
        if (!stopLeftCheck) {
            int LeftTile = GetTile({(float)(row - Index), FirstPos.y});
            if (LeftTile != -1) {
                LegalMoves.push_back(LeftTile);
                if (Board[LeftTile].id != Empty) stopLeftCheck = true;
                if (LeftTile < 0) LegalMoves.pop_back();
            } else stopLeftCheck = true;
        }

        //  RIGHT
        if (!stopRightCheck) {
            int RightTile = GetTile({(float)(row + Index), FirstPos.y});
            if (RightTile != -1) {
                LegalMoves.push_back(RightTile);
                if (Board[RightTile].id != Empty) stopRightCheck = true;
                if (RightTile < 0) LegalMoves.pop_back();
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

bool MoveIntegrity::Check_Queen(Vector2 FirstPos, Vector2 SecondPos)
{
    if (Check_Rook(FirstPos , SecondPos) == true) {
        return true;
    }
    return Check_Bishop(FirstPos , SecondPos);
}

bool MoveIntegrity::Check_King(Vector2 FirstPos, Vector2 SecondPos , bool CheckAttacks)
{
    int DistanceX = abs(FirstPos.x - SecondPos.x);
    int DistanceY = abs(FirstPos.y - SecondPos.y);
    int Tile = GetTile(FirstPos);
    int color = Board[Tile].color;

    if (DistanceX <= 1 && DistanceY <= 1) {
        // checks whether the tile the king is trying to go to is a dangerous square
        // CheckAttacks bool so that we don't get into an infinite recursion loop when checking opponent king
        if (CheckAttacks == true) {return !IsUnderAttack(color, SecondPos);
        }
        return true;
    }
    if (DistanceX == 2 && CheckAttacks == true) {
        Castle(FirstPos , SecondPos);
    }
    return false;
}

bool MoveIntegrity::IsUnderAttack(int color, Vector2 Pos)
{
    int OpponentColor = color * -1;
    int OpponentPawn = (color == Black) ? White_Pawn : Black_Pawn;


    for (int i = 0; i < 64; i++) {
        //loop through the whole board and recall CheckMove with bos of opponent piece and position of Friendly king
        if (Board[i].color != OpponentColor) continue;
        if (Board[i].id == OpponentPawn) {
            //Special condition for pawns as CheckMove() Returns Forward moves as true
            Vector2 FrontLeft = { (float)(i % 8), (float)(i / 8) };
            Vector2 FrontRight = { FrontLeft.x + 1 , FrontLeft.y - OpponentColor};
            FrontLeft.x = FrontLeft.x - 1 , FrontLeft.y = FrontLeft.y - OpponentColor ;

            if (FrontLeft == Pos || FrontRight == Pos) {
                return true;
            }
            continue;
        }
        Vector2 CurrentTile = { (float)(i % 8), (float)(i / 8) };
        if (CheckMove(CurrentTile, Pos, false)) {
            return true;
        }
    }
    return false;
}

bool MoveIntegrity::IsKingInCheck(int color , Vector2 FirstPos , Vector2 SecondPos)
{
        Piece TempBoard[64];
        std::copy(std::begin(Board), std::end(Board), std::begin(TempBoard));
        int king = (color == Black) ? Black_King : White_King;
        Vector2 KingPos = {0};
        for (int i = 0; i < 64; i++) {
            if (Board[i].id == king ) {
                KingPos = {(float)(i % 8), (float)(i / 8)};
            }
        }
        MakeMove(FirstPos , SecondPos);
    
        bool temp = IsUnderAttack(color , KingPos);
        if (temp == true) {
            std::copy(std::begin(TempBoard), std::end(TempBoard), std::begin(Board));
            return false;
        }
    return true;

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
        if (LegalMoves[i] == SecondPos) {
            return true;
        }
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
        Board[0 * 8 + col].startingTile = 0 * 8 + col;


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
        Board[7 * 8 + col].startingTile = 0 * 8 + col;
    }
}

bool MoveIntegrity::CheckMove(Vector2 FirstPos, Vector2 SecondPos , bool make )
{
    //todo those freaking pawns
    bool Answer = false;
    int OriginalTile = GetTile(FirstPos);
    int DestinationTile = GetTile(SecondPos);

    //Check basic cases like friendly fire / invalid tile
    if (Board[OriginalTile].color == Board[DestinationTile].color && make == true ) {
       return false;
    }
    if (SecondPos.x < 0 || SecondPos.x > 7
        ||SecondPos.y < 0 || SecondPos.y >7){return false;}


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
        case White_Queen:
        case Black_Queen:
            Answer = Check_Queen(FirstPos , SecondPos);
            break;
        case White_King:
        case Black_King:
            Answer = Check_King(FirstPos , SecondPos , make);
            break;
        case White_Pawn:
        case Black_Pawn:
            Answer = Check_Pawn(FirstPos , SecondPos);
            break;
        default:
            break;
    }

    if (Answer == true && make == true) {
        Answer = IsKingInCheck(Board[OriginalTile].color , FirstPos , SecondPos);
    }
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