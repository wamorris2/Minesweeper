#include <iostream>
#include <cstdlib>
#include "board.cpp"
#include "square.cpp"

// board: self-explanatory
// hide: don't show squares if they're not revealed
void displayBoard(Board board, bool hide = true)
{
  system("clear"); // clear screen

  // write column numbers
  std::cout << "   ";
  for (int i = 0; i < board.height(); i++)
    printf("%3d ", i);
  std::cout << '\n';

  for (int r=0; r<board.width(); r++){
    printf("%3d  ", r);  // write row number
    for (int c=0; c<board.height(); c++)
      {
	Square &sq = board(r,c);
	if (!sq.revealed() && hide)
	  if (sq.flagged()) // flagged by player
	    std::cout << "\033[0;34m" << "F" << "\033[0m"; // blue text
	  else // Unrevealed square
	    std::cout << "X";
	else
	  if (sq.isMine())
	    std::cout << "\033[0;31m" << "M" << "\033[0m"; // red text
	  else if (sq.neighbors() > 0)
	    std::cout << "\033[0;32m" << sq.neighbors() << "\033[0m"; // green text
	  else
	    std::cout << " ";
	std::cout << "   ";
      }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

int main(int argc, char **argv)
{
  // change12345678901234 for makefile
  bool playing = true;
  char option;
  while (playing)
    {
      int width = 14, height = 18, nMines = 40, seed = 23;
      std::cout << "Started Minesweeper!" << std::endl;
      std::cout << "(D)efault or (C)ustom: ";
      std::cin >> option;
      switch (option) {
	case 'C': case 'c':
	  do {
            std::cout << "Enter Width [1,18]: ";
            std::cin >> width;
	  } while (width <= 0 || width >= 19);
	  do {
            std::cout << "Enter height [1,18]: ";
            std::cin >> height;
	  } while (height <= 0 || height >= 19);
	  do {
            std::cout << "Enter amount of mines [0, " << width * height << "]: ";
	    std::cin >> nMines;
	  } while (nMines < 0 || nMines > width * height);
          std::cout << "Enter Random Seed: ";
          std::cin >> seed;
	  break;
	case 'D': case 'd': break;
	default: continue;
      }
      
      std::cout << "There are " << nMines << " mines in this " << width << " by " << height << " grid!" << std::endl;
      system("sleep 0.5");
      std::cout << "Good Luck!" << std::endl;
      system("sleep 1.0");

      srand(seed);
      Board board(width,height,nMines);
      displayBoard(board);
      bool ingame = true;
      int row, column;
      char flag;
      while(ingame)
	{
	  do {
	    std::cout << "Enter a row and column (r c): ";
	    std::cin >> row >> column;
	  } while (row < 0 && row >= width && column < 0 && column >= height);
	  std::cout << "Flag/Unflag? y or n: ";
	  std::cin >> flag;
	  Square& sq = board(row, column);
	  if (flag == 'y' || flag == 'Y')
	    sq.flipFlag();
	  if (!sq.flagged())
	    {       
	    if (sq.isMine())
	      {
		sq.reveal();
		std::cout << "You Lost!" << std::endl;
		ingame = false;
	      }
	    else if (sq.neighbors() > 0)
	      sq.reveal();
	    else
	      board.check(row,column);
	    }
	  else
	    {
	      std::cout << "That square is flagged!" << std::endl;
	    }
	  displayBoard(board);
	}
      displayBoard(board, false);
      std::cout << "(Q)uit or (P)lay again: ";
      std::cin >> option;
      switch (option) {
        case 'Q': case 'q':
          playing = false;
	  break;
	case 'P': case 'p': default: break;
      }
    }
  return 0;
}
