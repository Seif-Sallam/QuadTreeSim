#pragma once
#include <iostream>
#include <string>
#include <array>
#include <SFML/Graphics.hpp>
#include "Particle.h"

class QuadTree
{
public:
    QuadTree(const sf::FloatRect &boundry);
    bool Insert(Particle *particle);

    void Render(sf::RenderWindow &window);
    void Clean();
    ~QuadTree();

private:
    void SubDivide();

    sf::FloatRect m_Boundry;

    QuadTree *m_NorthWest;
    QuadTree *m_NorthEast;
    QuadTree *m_SouthWest;
    QuadTree *m_SouthEast;

    std::array<Particle *, 4> points;
    int m_NumberOfElements = 0;
    bool m_Divided = false;
};
