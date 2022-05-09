#include "square.hpp"

Square::Square()
{
  _neighbors = 0;
  _mine = false;
  _revealed = false;
  _flagged = false;
}

void Square::addNeighbor(void)
{
  _neighbors += 1;
}

int Square::neighbors(void)
{
  return _neighbors;
}

void Square::setMine(bool m)
{
  _mine = m;
}

bool Square::isMine(void)
{
  return _mine;
}

void Square::reveal(void)
{
  _revealed = true;
}

bool Square::revealed(void)
{
  return _revealed;
}

void Square::flipFlag(void)
{
  _flagged = !_flagged;
}

bool Square::flagged(void)
{
  return _flagged;
}
