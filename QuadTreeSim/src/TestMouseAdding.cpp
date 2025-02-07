#include "TestMouseAdding.h"
#include "Application.h"

TestMouseAdding::TestMouseAdding()
    : m_ParticlesNum(0u), m_ParticleSize(sf::Vector2f(2.0f, 2.0f)), m_MaxParticlesNum(5000), m_ShowParticles(true)
{
    sf::Vector2u windowRes = Application::GetWindowRes();
    sf::FloatRect boundry = {5, 5, windowRes.x - 10.f, windowRes.y - 10.f};
    m_Tree = new QuadTree(boundry);
    m_Particles.reserve(1000);
}

void TestMouseAdding::Update(const sf::Time &dt)
{
    if (ImGui::GetIO().WantCaptureMouse)
        return;
    sf::Vector2f mousePos = Application::GetMousePos();
    if (m_ParticlesNum < m_MaxParticlesNum)
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_Particles.push_back(new Particle(mousePos, m_ParticleSize));
            m_Tree->Insert(m_Particles.back());
            m_ParticlesNum++;
        }
}

void TestMouseAdding::HandleEvents(const sf::Event &event)
{
}

void TestMouseAdding::Render(sf::RenderWindow &window)
{
    m_Tree->Render(window, m_ShowParticles);
}

void TestMouseAdding::OnImGuiRender()
{
    ImGui::Text("Number of current Particles: %d\n", m_ParticlesNum);
    ImGui::Checkbox("Show Particles", &m_ShowParticles);
}

TestMouseAdding::~TestMouseAdding()
{
    m_Tree->Clean();
    for (int i = 0; i < m_Particles.size(); i++)
    {
        delete m_Particles[i];
        m_Particles[i] = nullptr;
    }
    m_ParticlesNum = 0;

    delete m_Tree;
}