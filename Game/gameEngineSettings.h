#ifndef __GAME_ENGINE_SETTINGS
#define __GAME_ENGINE_SETTINGS

#include "../Algorithms/algorithmRegistry.h"

struct GameEngineSettings
{
  int numberOfGames = 20;
  int difficulty = 1000;
  bool showMoves = false;
  Algorithm * algorithm = &algorithmRegistry.manhattanDistanceAlgorithm;
} gameEngineSettings;

#endif