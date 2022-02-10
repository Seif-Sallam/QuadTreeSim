#include "Application.h"
sf::Vector2u Application::s_WindowRes = sf::Vector2u(800, 600);

const sf::Vector2u Application::GetWindowRes()
{
    return s_WindowRes;
}

Application::Application()
{
    InitWindow();

    InitAppStates();
}

void Application::Run()
{
    while (m_Window->isOpen())
    {
        sf::Time dt = this->m_Clock.restart();
        HandleEvents();

        Update(dt);

        ImGuiUpdate(dt);

        Render();
    }
}

Application::~Application()
{
    ImGui::SFML::Shutdown();
    m_Window->close();
    delete m_Window;
    m_Window = nullptr;
}

bool Application::InitWindow()
{
    m_Window = nullptr;
    m_Window = new sf::RenderWindow(sf::VideoMode(s_WindowRes.x, s_WindowRes.y), "QuadTree Sim", sf::Style::Titlebar);
    if (m_Window == nullptr)
    {
        std::cerr << "Couldn't Initialize Window!\n";
        return false;
    }
    m_View.setSize(s_WindowRes.x, s_WindowRes.y);                             // making the size as the resolution of the simulation
    m_View.setCenter(sf::Vector2f(s_WindowRes.x / 2.f, s_WindowRes.y / 2.f)); // making the center 0 and 0

    ImGui::SFML::Init(*m_Window, true);
}

bool Application::InitAppStates()
{
}

void Application::HandleEvents()
{
    sf::Event event;
    while (m_Window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            this->m_Window->close();
    }
}

void Application::Update(const sf::Time &dt)
{
}

void Application::ImGuiUpdate(const sf::Time &dt)
{
    ImGui::SFML::Update(*m_Window, dt);
}

void Application::Render()
{
    m_Window->setView(m_View);
    m_Window->clear();
    ImGui::SFML::Render(*m_Window);
    m_Window->display();
}