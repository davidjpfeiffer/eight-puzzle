#ifndef __RANDOM_SERVICE
#define __RANDOM_SERVICE

#include <random>
#include <chrono>
#include <climits>

class RandomService
{
public:
  RandomService()
  {
    seedRandomNumberGenerator();
    defaultRandomEngine = getDefaultRandomEngine();
    uniformIntDistribution = getUniformIntDistribution();
  }

  int getRandomNumber(int inclusiveMin, int inclusiveMax)
  {
    return uniformIntDistribution(randomNumberGenerator) % (inclusiveMax - inclusiveMin + 1) + inclusiveMin;
  }

  std::mt19937 randomNumberGenerator;
  std::default_random_engine defaultRandomEngine;
  std::uniform_int_distribution<std::mt19937::result_type> uniformIntDistribution;

private:
  std::default_random_engine getDefaultRandomEngine()
  {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    return std::default_random_engine(seed);
  }

  std::uniform_int_distribution<std::mt19937::result_type> getUniformIntDistribution()
  {
    return std::uniform_int_distribution<std::mt19937::result_type>(0, INT_MAX);
  }

  void seedRandomNumberGenerator()
  {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    randomNumberGenerator.seed(seed);
  }
} randomService;

#endif