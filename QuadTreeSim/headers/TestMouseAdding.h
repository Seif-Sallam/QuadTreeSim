#pragma once
#include <vector>

#include "TestMenu.h"
#include "Particle.h"
#include "QuadTree.h"

class TestMouseAdding : public Test
{
public:
    TestMouseAdding();
    void Update(const sf::Time &dt) override;
    void HandleEvents(const sf::Event &event) override;
    void Render(sf::RenderWindow &window) override;
    void OnImGuiRender() override;
    ~TestMouseAdding();

private:
    uint32_t m_ParticlesNum;
    QuadTree *m_Tree;
    std::vector<Particle *> m_Particles;
    const sf::Vector2f m_ParticleSize;
    const uint32_t m_MaxParticlesNum;
    bool m_ShowParticles;
};