#ifndef __ALGORITHM
#define __ALGORITHM

#include "./board.h"

class Algorithm
{
public:
  virtual int quantifyBoardState(Board * board) = 0;
};

#endif