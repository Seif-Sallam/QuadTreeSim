#pragma once
#include "TestMenu.h"
#include "QuadTree.h"
#include "Particle.h"
#include <array>

class QuadTreeQueryTest : public Test
{
public:
    QuadTreeQueryTest();
    void Update(const sf::Time &dt) override;
    void HandleEvents(const sf::Event &event) override;
    void Render(sf::RenderWindow &window) override;
    void OnImGuiRender() override;
    ~QuadTreeQueryTest();

private:
    void InitParticles();

private:
    QuadTree *m_Tree;
    std::array<Particle *, 1000> m_Particles;
    sf::RectangleShape m_RangeQuery;
    int32_t m_ChecksCount;
    int32_t m_FoundParticlesNum;
};