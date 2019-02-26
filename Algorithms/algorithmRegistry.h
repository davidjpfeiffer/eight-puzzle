#ifndef __ALGORITHM_REGISTRY
#define __ALGORITHM_REGISTRY

#include "./manhattanDistanceAlgorithm.h"
#include "./misplacedTilesAlgorithm.h"

struct AlgorithmRegistry
{
  ManhattanDistanceAlgorithm manhattanDistanceAlgorithm;
  MisplacedTilesAlgorithm misplacedTilesAlgorithm;
} algorithmRegistry;

#endif