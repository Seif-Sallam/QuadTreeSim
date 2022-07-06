#pragma once
#include <array>
#include "TestMenu.h"
#include "Particle.h"
#include "QuadTree.h"
class CollisionTest : public Test
{
public:
    CollisionTest();
    void Update(const sf::Time &dt) override;
    void HandleEvents(const sf::Event &event) override;
    void Render(sf::RenderWindow &window) override;
    void OnImGuiRender() override;
    ~CollisionTest();

private:
    void InitParticles();
    void CheckCollision();

private:
    std::array<Particle *, 3000> m_Particles;
    QuadTree *m_Tree;
};