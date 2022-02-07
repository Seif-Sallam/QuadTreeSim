#pragma once
#include <stdio.h>
#include <SFML/System/Vector2.hpp>
#ifdef DEBUG_ENABLED
#define LOG(X, ...) printf(X, ##__VA_ARGS__)
#else
#define LOG(X)
#endif