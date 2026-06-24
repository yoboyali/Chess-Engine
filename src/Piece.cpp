//
// Created by Ali Hamdy on 23/06/2026.
//

#include "Piece.h"
#include "Includes.h"

Pawn::Pawn(int color):Piece()
{
    id = 10;
    this->color = color;
    this->startingTile = color == Black ? 6 : 1;

}
