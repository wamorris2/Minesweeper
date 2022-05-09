#include <iostream>
#include <cstdlib>
#include <cassert>
#include "board.hpp"
#include "square.hpp"

Board::Board(const int w, const int h, const int n)
  : _width(w), _height(h), _numMines(n)
{
  _board = std::vector<Square>(_width * _height);
  _visited = std::vector<bool>(_width * _height);
  int nM = n;
  for (int i=0; i<_width && nM > 0; i++)
    for (int j=0; j<_height && nM > 0; j++)
      {
	int index = i * _width + j;	
	float rand = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
	float mChance = static_cast<float>(nM) / static_cast<float>(_width*_height-index);
	if (rand<=mChance) {
	  this->placeMine(i, j);
	  nM--;
	}
      }
}

void Board::placeMine(int row, int col)
{
  this->operator()(row, col).setMine(true);

  for (int r = std::max(row - 1, 0); r < std::min(row + 2, _width); r++)
    for (int c = std::max(col - 1, 0); c < std::min(col + 2, _height); c++)
	this->operator()(r, c).addNeighbor();
}

Square& Board::operator()(int row, int col)
{
  assert(row >= 0 && row < _width && col >= 0 && col < _height);
  return _board[row * _height + col];
}

Square* Board::getSquare(int row, int col)
{
  row = (row < 0) ? 0 : ((row >= _width) ? _width - 1 : row);
  col = (col < 0) ? 0 : ((col >= _height) ? _height - 1 : col);
  return &_board[row * _height + col];
}

void Board::check(int row, int col)
{
  // clamp row
  row = (row < 0) ? 0 : ((row >= _width) ? _width - 1 : row);
  // clamp column
  col = (col < 0) ? 0 : ((col >= _height) ? _height - 1 : col);
  int index = row * _height + col;  
  // check if we've been here before
  if (_visited[index])
    return;
  else
    _visited[index] = true;

  // get the square at (row, col)
  Square &sq = _board[index];
  
  if (sq.isMine())
    return;
  
  sq.reveal();

  // stop if not empty
  if (sq.neighbors() > 0)
    return;

  // check neighbors
  for (int r = std::max(row - 1, 0); r < std::min(row + 2, _width); r++)
    for (int c = std::max(col - 1, 0); c < std::min(col + 2, _height); c++)
	this->check(r, c);
  
  // reset _visited
  if (_visited.size())
    _visited.clear();
}
