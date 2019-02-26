#ifndef __MANHATTAN_DISTANCE_ALGORITHM
#define __MANHATTAN_DISTANCE_ALGORITHM

#include <utility>
#include <math.h>
#include <cmath>

#include "../Game/algorithm.h"

class ManhattanDistanceAlgorithm: public Algorithm
{
  int quantifyBoardState(Board * board)
  {
    int value = 0;

    for (int i = 0; i < board->boardSize; i++)
    {
      int v1 = i, v2 = (*board)[i];
      int row1 = std::floor(v1 / 3), col1 = v1 % 3;
      int row2 = std::floor(v2 / 3), col2 = v2 % 3;
      value += std::abs(row1 - row2) + std::abs(col1 - col2);
    }

    return value;
  }
} manhattanDistanceAlgorithm;

#endif