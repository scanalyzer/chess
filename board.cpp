//
//  board.cpp
//  Object Oriented Chess
//
//  Created by Brooks Robison on 3/17/16.
//  Copyright © 2016 Dan McDaniel. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "piece.h"
#include "move.h"
#include "position.h"
#include "board.h"

//using namespace std;


// Two statics in the Piece class: the simple flag indicating that we
//    have the Test board displayed instead of the colorful board, and
//    the currentMove so each piece can tell if it's move was the last move
//bool Piece::fSimple = true;   // not starting off in Test mode
//int  Piece::currentMove = 0;   // starting at move 0

//NON-MEMBER FUNCTIONS//

/*************
 * Draw Menu *
 *************/
void showMenu()
{
   std::cout << "Options:"                                   << std::endl
   << " ?      Display these options"                        << std::endl
   << " b2b4   Specify a move using the Smith Notation"      << std::endl
   << " read   Read a saved game from a file"                << std::endl
   << " test   Simple display for test purposes"             << std::endl
   << " quit   Leave the game. You will be prompted to save" << std::endl
   << " help   Show valid moves for given piece"             << std::endl
   << " rank   Compute the strenght of a given position"     << std::endl;
}

/**********
 * Prompt *
 **********/
inline void prompt(char prompt[256], char response[256])
{
   std::cout << prompt;
   std::cin  >> response;
}

/********************
 * Load - From File *
 ********************/
void Board::load(std::string filename)
{
   //char move[8];
   std::string move;
   //Reset board
   init();
   
   //Reset move array
   history.empty();
   history.clear();
   
   std::ifstream fin(filename);
   
   if (!fin.fail())
      while (fin >> move)
      {
         bool errorFlag = true;
         std::string error = "";
         
         //Capture character
         char c = move[4];
         if (!(c == '\0' || c == 'p' || c == 'r' || c == 'n'
               || c == 'b' || c == 'q' || c == 'k'))
            error = "Unknown promotion piece specification";
         else
            if (move[0] >= 'a' && move[0] <= 'h')
               if (move[1] >= '0' && move[1] <= '8')
                  if (move[2] >= 'a' && move[2] <= 'h')
                     if (move[3] >= '0' && move[3] <= '8')
                     {
                        char p = squares[move[1] - 49][move[0] - 97]->getLetter();
                        
                        if (p == 'p' || p == 'r' || p == 'n' ||
                            p == 'b' || p == 'q' || p == 'k' ||
                            p == 'P' || p == 'R' || p == 'N' ||
                            p == 'B' || p == 'Q' || p == 'K')
                        {
                           errorFlag = false;
                           //makeMove(board, move);
                           //moveArray.push_back(move);
                           Move m(move, *this);
                           m.execute();
                        }
                        else error =
                           "No piece in the source coordinates position";
                     }
         //Errors below in styleChecker are unfounded.
                     else error = "Invalid format of destination coordinates";
                     else error =    "Invalid format of destination coordinates";
                     else error =       "Invalid format of source coordinates";
                     else error =          "Invalid format of source coordinates";
         
         if (errorFlag)
         {
            std::cout << "Error parsing file " << filename
            << " with move '"        << move
            << "': "                 << error       << std::endl;
            throw(error);
            return;
         }
      }
   else
      std::cout << "Unable to open file " << filename << " for input." << std::endl;
   
   //Close the file.
   fin.close();
}


//MEMBER FUNCTIONS//

/**********************
 * Interact with User *
// **********************/
//bool Board::interact()
//{
//   bool isTestMode = false;
//   char filename[256] = {'\0'};
//   char moveOld[8] = { '\0' };
//    
//   
//   
//   while (moveOld[0] != 'q') // check for full word
//   {
//      //prompt for a move
//      if (history.size() % 2 == 0)
//         std::cout << "(White): ";
//      else
//         std::cout << "(Black): ";
//      
//      std::string moveString;
//      std::cin >> moveString;
//      
//      Move move(moveString, *this);
//     
//      //moves
//      if (moveString[0] >= 97 && moveString[0] <= 104) //first letter is a-h
//      {
//         move.parse();
//         //move.validate();
//         history.push_back(moveString);
//         move.execute();
//         drawTest();
//      }
//      
//      //commands
//      else
//      {
//         switch (moveString[0])
//         {
//            case '?' :         //help
//               showMenu();
//               break;
//            case 'r' :         //read
//               try
//            {
//               prompt((char *)"Filename: ", filename);
//               load(filename);
//               drawTest();
//            }
//               catch (std::string error)
//            {
//               std::cout << "";// "ERROR DETECTED";
//            }
//               break;
//            case 't' :         //test output
//               isTestMode = !isTestMode;
//               //drawTest();
//               draw();
//               break;
//            case 'l' :         //list moves in array
//               //list(moveArray);
//               break;
//            case 'q' :
//               return false;
//               break;          //quit
//            default:           //unknown input
//               std::cout << "Error: Unknown Input"
//               << "	Type ? for more options"               << std::endl;
//               break;
//         }
//      }
//   }
//   std::cout << "To save a game, please specify the filename." << std::endl
//   << "    To quit without saving a file, just press <enter>"  << std::endl;
//   std::string response;
//   response = std::cin.get();
//   if (std::cin.get() != '\n');
//   //save(response, moveArray);
//   std::cin.ignore();
//   return true;
//}

void Board::interact()
{
   bool isTestMode = false;
   bool quit = false;
   
   do
   {
      // who's turn is it? yours or mine?
      switch (history.size() % 2)
      {
         case 0:
            std::cout << "(White): ";
            break;
         case 1:
            std::cout << "(Black): ";
            break;
      }
      
      std::string moveString;
      std::cin >> moveString;
      
      if (moveString == "?")
         showMenu();
      else if (moveString == "read")
         std::cout << "read" << std::endl;
         //readFile(moveHistory, board, testMode);
      else if (moveString == "test")
         {
            isTestMode = !isTestMode;
            //draw(board, testMode);
         }
      else if (moveString == "quit")
         quit = true;
      else if(moveString == "help")
      {
         std::cout << "What piece would you like to find the moves for?" << std::endl;
         char r, c = '\0';
         std::cin >> c >> r;
         
         Move theMove(moveString);
         theMove.parse
         squares[r][c]->getMoves(this);
         
         std::cout << "Possible moves are:" << std::endl;
         
         int count = 0;
         for (std::vector<std::string>::iterator it = squares[r][c].piece.posMoves.begin();
              it != squares[r][c].piece.posMoves.end();
              ++it)
         {
            std::cout << squares[r][c].piece.posMoves[count++] << std::endl;
         }
      }
      
      else if(moveString == "rank")
         std::cout << "This feature is not available" << std::endl;
      else
      {
         try
         {
            // take users input as an attempt to make a move on the
            // board
            Move move(moveString, *this);
            move.parse();
            //move.validate();
            move.execute();
            history.push_back(moveString);
            drawTest();
         }
         catch (std::string error)
         {
            std::cout << "Error in move \'" << moveString << "\': " << error << std::endl;
            std::cout << "      Type ? for more options\n";
         }
      }
   }
   while (quit == false);
   
   //writeFile(moveHistory);
   
   return;
   
}



/**************
 * Draw Board *
 **************/
void Board::draw()
{
   std::cout << CLEAR;
   std::cout << "   a  b  c  d  e  f  g  h " << std::endl; // I prefer endl.
   bool white = true; //for checkerboard pattern
   for (int r = 7; r >= 0; r--)
   {
      std::cout << r + 1 << " "; //row headers
      for (int c = 0; c < 8; c++)
      {
         //Formatting Board - false styleChecker errors on these lines, too...
         if (white) std::cout << ((this->squares[r][c]->getLetter() > 97) ? WW : WB); //white/black piece
         else       std::cout << ((this->squares[r][c]->getLetter() > 97) ? RW : RB); //white/black piece
         
         //Output
         //ChessPiece piece = squares[r][c].getPiece();
         if (this->squares[r][c]->getLetter() != '\0') //occupied if not null
            std::cout << " " << this->squares[r][c]->getLetter() << " ";
         else                     //free
            std::cout << "   ";
         std::cout << BW;              //reset formatting
         
         //Flip the color bit
         white = !white; // When is white now white?  Now.
      }
      white = !white;    // And now, too.
      std::cout << std::endl;
   }
}
//*/

/*******************
 * Draw Test Board *
 *******************/
void Board::drawTest()
{
   //std::cout << CLEAR;
   std::cout << "  abcdefgh" << std::endl;   // I prefer endl over '\0'.
   for (int r = 7; r >= 0; r--)
   {
      std::cout << r + 1 << " ";        //row headers
      for (int c = 0; c <= 7; c++)
         //if (this->squares[r][c].piece->getLetter() != '\0')
         if (this->squares[7-r][c]->getLetter() != ' ')  //occupied if not null
            std::cout << this->squares[7-r][c]->getLetter();
      //std::cout << 'z';
         else                      //free
            std::cout << " ";
      std::cout << std::endl;
   }
}

/********************
 * Initialize Board *
 ********************/
void Board::init()
{
   //White
   this->squares[0][4] = new King(false); //true = isWhite
   this->squares[0][3] = new Queen(false);
   this->squares[0][0] = new Rook(false); //Left
   this->squares[0][7] = new Rook(false); //Right
   this->squares[0][1] = new Knight(false);
   this->squares[0][6] = new Knight(false);
   this->squares[0][2] = new Bishop(false);
   this->squares[0][5] = new Bishop(false);
   
   this->squares[1][0] = new Pawn(false);
   this->squares[1][1] = new Pawn(false);
   this->squares[1][2] = new Pawn(false);
   this->squares[1][3] = new Pawn(false);
   this->squares[1][4] = new Pawn(false);
   this->squares[1][5] = new Pawn(false);
   this->squares[1][6] = new Pawn(false);
   this->squares[1][7] = new Pawn(false);
   
   //The great divide
   for (int r = 5; r >= 2; r--)
      for (int c = 0; c <= 7; c++)
         this->squares[r][c] = new Space();
   
   //Black
   this->squares[6][0] = new Pawn(true);
   this->squares[6][1] = new Pawn(true);
   this->squares[6][2] = new Pawn(true);
   this->squares[6][3] = new Pawn(true);
   this->squares[6][4] = new Pawn(true);
   this->squares[6][5] = new Pawn(true);
   this->squares[6][6] = new Pawn(true);
   this->squares[6][7] = new Pawn(true);
   
   this->squares[7][0] = new Rook(true);
   this->squares[7][7] = new Rook(true);
   this->squares[7][1] = new Knight(true);
   this->squares[7][6] = new Knight(true);
   this->squares[7][2] = new Bishop(true);
   this->squares[7][5] = new Bishop(true);
   this->squares[7][3] = new Queen(true);
   this->squares[7][4] = new King(true);
}


