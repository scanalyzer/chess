//
//  piece.h
//  Object Oriented Chess
//
//  Created by Brooks Robison on 3/17/16.
//  Copyright © 2016 Dan McDaniel. All rights reserved.
//

#ifndef piece_h
#define piece_h

class Piece
{
public:
    Piece(bool isWhite) : isWhite(isWhite) {                 }
    bool getIsWhite() const                { return isWhite; }
    virtual char getLetter() const = 0;
    virtual int getScore()   const = 0;
protected:
    bool isWhite;
};

class Space : public Piece
{
public:
    Space() : Piece(isWhite) {}
    
    virtual int getScore() const   { return 0;   }
    virtual char getLetter() const { return ' '; }
    
};

class King : public Piece
{
public:
    King(bool isWhite) : Piece(isWhite) {};
    char getLetter() const {return isWhite ? 'k' : 'K';}
    int getScore() const {return isWhite ? 100 : -100;}
};

class Queen : public Piece
{
public:
    Queen(bool isWhite) : Piece(isWhite) {};
    char getLetter() const {return isWhite ? 'q' : 'Q';}
    int getScore() const {return isWhite ? 10 : -10;}
};

class Bishop : public Piece
{
public:
    Bishop(bool isWhite) : Piece(isWhite) {};
    char getLetter() const {return isWhite ? 'b' : 'B';}
    int getScore() const {return isWhite ? 100 : -100;}
};

class Knight : public Piece
{
public:
    Knight(bool isWhite) : Piece(isWhite) {};
    char getLetter() const {return isWhite ? 'n' : 'N';}
    int getScore() const {return isWhite ? 10 : -10;}
};

class Rook : public Piece
{
public:
    Rook(bool isWhite) : Piece(isWhite) {};
    char getLetter() const {return isWhite ? 'r' : 'R';}
    int getScore() const {return isWhite ? 1 : -1;}
};


class Pawn : public Piece
{
public:
    Pawn(bool isWhite) : Piece(isWhite) {};
    char getLetter() const {return isWhite ? 'p' : 'P';}
    int getScore() const {return isWhite ? 1 : -1;}
};

#endif /* piece_h */