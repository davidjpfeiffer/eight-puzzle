#include <iostream>

#include "./Algorithms/manhattanDistanceAlgorithm.h"
#include "./gameEngine.h"

using namespace std;

int main()
{
  ManhattanDistanceAlgorithm algorithm;
  GameEngine gameEngine;
  gameEngine.executeAlgorithm(&algorithm);
}