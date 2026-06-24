#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
    int id = 0;
    int color = 0;
    int startingTile = 0;
    virtual ~Piece() = default;  //prevents slicing
};

class Pawn : public Piece {
public:
    Pawn(int color);
    bool enPassant = false;
};

#endif