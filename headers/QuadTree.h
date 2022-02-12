#pragma once
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.h"

class QuadTree
{
public:
    QuadTree(const sf::FloatRect &boundry);
    bool Insert(Particle *particle);
    void Query(const sf::FloatRect &range, std::vector<Particle *> &foundParticles, int *count = nullptr);
    void Render(sf::RenderWindow &window, bool renderPoints);
    void Clean();
    ~QuadTree();

private:
    void SubDivide();

    sf::FloatRect m_Boundry;

    QuadTree *m_NorthWest;
    QuadTree *m_NorthEast;
    QuadTree *m_SouthWest;
    QuadTree *m_SouthEast;

    std::array<Particle *, 4> m_Points;
    int m_NumberOfElements = 0;
    bool m_Divided = false;
};
