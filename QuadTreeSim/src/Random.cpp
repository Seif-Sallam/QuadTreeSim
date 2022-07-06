#include "Random.h"

std::mt19937 Random::randomGen;
Random Random::s_Instance;

float Random::GetRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> gen(min, max);
    return gen(randomGen);
}

int Random::GetRandomInt(int min, int max)
{
    std::uniform_int_distribution<int> gen(min, max);
    return gen(randomGen);
}