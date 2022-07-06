#include "QuadTreeQueryTest.h"
#include "Application.h"
#include "Random.h"

QuadTreeQueryTest::QuadTreeQueryTest()
{
    //Generate all particles
    InitParticles();
    m_RangeQuery.setFillColor(sf::Color::Transparent);
    m_RangeQuery.setOutlineThickness(2.f);
    m_RangeQuery.setOutlineColor(sf::Color::Green);
    m_RangeQuery.setSize(sf::Vector2f(100.0f, 100.0f));
}

void QuadTreeQueryTest::Update(const sf::Time &dt)
{
    sf::Vector2f mousePos = Application::GetMousePos();
    float length = m_RangeQuery.getSize().x / 2.f;
    m_RangeQuery.setPosition(sf::Vector2f(mousePos.x - length, mousePos.y - length));
    std::vector<Particle *> foundParticles;
    foundParticles.reserve(m_Particles.size() / 2);
    m_ChecksCount = 0;

    m_Tree->Query(m_RangeQuery.getGlobalBounds(), foundParticles, &m_ChecksCount);
    for (int i = 0; i < foundParticles.size(); i++)
        foundParticles[i]->HighlightOnce();
    m_FoundParticlesNum = foundParticles.size();
}

void QuadTreeQueryTest::HandleEvents(const sf::Event &event)
{
}

void QuadTreeQueryTest::Render(sf::RenderWindow &window)
{
    m_Tree->Render(window, true);
    window.draw(m_RangeQuery);
}

void QuadTreeQueryTest::OnImGuiRender()
{
    ImGui::Text("Number of points: %ld", m_Particles.size());
    ImGui::Text("Number of checks: %d", m_ChecksCount);
    ImGui::Text("Number of found particles: %d", m_FoundParticlesNum);
    static float length = m_RangeQuery.getSize().x;
    ImGui::DragFloat("Box Length", &length, 0.5f, 10.0f, 400.f);
    if (ImGui::Button("Submit"))
        m_RangeQuery.setSize(sf::Vector2f(length, length));
}

QuadTreeQueryTest::~QuadTreeQueryTest()
{
    m_Tree->Clean();
    for (int i = 0; i < m_Particles.size(); i++)
        delete m_Particles[i];
    delete m_Tree;
}

void QuadTreeQueryTest::InitParticles()
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