#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "square.hpp"

class Board {
public:
  Board(const int w, const int h, const int n);
  Square& operator()(int row, int col);
  Square* getSquare(int row, int col);
  inline const int width() { return _width; }
  inline const int height() { return _height; }
  void check(int row, int col);
private:
  void placeMine(int row, int col);
  std::vector<Square> _board;
  std::vector<bool> _visited;
  int _width, _height;
  int _numMines;
};

#endif
