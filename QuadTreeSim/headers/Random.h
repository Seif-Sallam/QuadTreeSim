#pragma once
#include <time.h>
#include <random>

class Random
{
public:
    static float GetRandomFloat(float min, float max);
    static int GetRandomInt(int min, int max);

private:
    inline Random()
    {
        randomGen.seed(time(0));
    }
    static Random s_Instance;
    static std::mt19937 randomGen;
};
