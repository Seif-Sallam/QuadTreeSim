#include "CollisionTest.h"
#include "Random.h"
#include "Application.h"

CollisionTest::CollisionTest()
{
    InitParticles();
}

void CollisionTest::Update(const sf::Time &dt)
{
    // Construct Tree & Update
    m_Tree->Clean();
    for (int i = 0; i < m_Particles.size(); i++)
    {
        m_Particles[i]->RandomMove();
        m_Tree->Insert(m_Particles[i]);
    }

    // Check Collision
    CheckCollision();
}

void CollisionTest::HandleEvents(const sf::Event &event)
{
}

void CollisionTest::Render(sf::RenderWindow &window)
{
    m_Tree->Render(window, true);
}

void CollisionTest::OnImGuiRender()
{
}

CollisionTest::~CollisionTest()
{
    for (int i = 0; i < m_Particles.size(); i++)
        delete m_Particles[i];
}

void CollisionTest::InitParticles()
{
    sf::Vector2u windowRes = Application::GetWindowRes();
    m_Tree = new QuadTree(sf::FloatRect(5.0f, 5.0f, windowRes.x - 10.0f, windowRes.y - 10.0f));
    auto GetRandomVec2f = [](sf::Vector2f min, sf::Vector2f max)
    {
        sf::Vector2f vec;
        vec.x = Random::GetRandomFloat(min.x, max.x);
        vec.y = Random::GetRandomFloat(min.y, max.y);
        return vec;
    };

    sf::Vector2f min(5.0f, 5.0f);
    sf::Vector2f max(windowRes.x - 10.0f, windowRes.y - 10.0f);
    sf::Vector2f particleSize(3.0f, 3.0f);
    for (int i = 0; i < m_Particles.size(); i++)
    {
        m_Particles[i] = new Particle(GetRandomVec2f(min, max), particleSize);
        m_Tree->Insert(m_Particles[i]);
    }
}

void CollisionTest::CheckCollision()
{
}