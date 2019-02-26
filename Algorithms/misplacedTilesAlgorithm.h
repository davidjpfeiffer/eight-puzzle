#ifndef __MISPLACED_TILES_ALGORITHM
#define __MISPLACED_TILES_ALGORITHM

#include "../algorithm.h"

class MisplacedTilesAlgorithm: public Algorithm
{
  int quantifyBoardState(Board * board)
  {
    int value = 0;

    for (int i = 0; i < board->boardSize; i++)
    {
      if ((*board)[i] != i)
      {
        value++;
      }
    }

    return value;
  }
} misplacedTilesAlgorithm;

#endif