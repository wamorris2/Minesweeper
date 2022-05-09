#include <iostream>
#include <cstdlib>
#include "board.cpp"
#include "square.cpp"

void displayBoard(Board board, bool hide = true)
{
  system("clear");
  std::cout << "   ";
  for (int i = 0; i < board.height(); i++)
    printf("%3d ", i);
  std::cout << '\n';
  for (int r=0; r<board.width(); r++){
    printf("%3d  ", r);
    for (int c=0; c<board.height(); c++)
      {
	Square &sq = board(r,c);
	if (!sq.revealed() && hide)
	  if (sq.flagged())
	    std::cout << "\033[0;34m" << "F" << "\033[0m";
	  else
	    std::cout << "X";
	else
	  if (sq.isMine())
	    std::cout << "\033[0;31m" << "M" << "\033[0m";
	  else if (sq.neighbors() > 0)
	    std::cout << "\033[0;32m" << sq.neighbors() << "\033[0m";
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
  while (playing)
    {
      int width = 14, height = 18, nMines = 40;
      std::cout << width << " by " << height << '\n';
      std::cout << "Started Minesweeper! seed: ";
      unsigned int seed;
      std::cin >> seed;
      srand(seed);

      Board board(width,height,nMines);
      displayBoard(board);
      bool ingame = true;
      while(ingame)
	{
	  std::cout << "Enter a row and column (r c): ";
	  int row, column;
	  std::cin >> row >> column;
	  std::cout << "Flag/Unflag? y or n: ";
	  char flag;
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
      char option;
      std::cin >> option;
      if (option == 'Q' || option == 'q')
	playing = false;
    }
  return 0;
}
