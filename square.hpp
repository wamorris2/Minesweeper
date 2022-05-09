#ifndef SQUARE_HPP
#define SQUARE_HPP

class Square{
public:
  Square();
  int neighbors(void);
  void addNeighbor(void);
  void setMine(bool m);
  bool isMine(void);
  bool revealed(void);
  void reveal(void);
  bool flagged(void);
  void flipFlag(void);
private:
  int _neighbors;
  bool _mine;
  bool _revealed;
  bool _flagged;
};

#endif
