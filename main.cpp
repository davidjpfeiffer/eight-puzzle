#include <iostream>

#include "./Game/gameEngine.h"

using namespace std;

int main()
{
  GameEngine gameEngine(gameEngineSettings);
  gameEngine.play();
}