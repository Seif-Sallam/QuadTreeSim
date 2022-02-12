#include "Application.h"
#include "TestMouseAdding.h"
#include "QuadTreeQueryTest.h"

sf::Vector2u Application::s_WindowRes = sf::Vector2u(800, 600);
sf::RenderWindow *Application::m_Window = nullptr;
const sf::Vector2u Application::GetWindowRes()
{
    return s_WindowRes;
}

const sf::Vector2f Application::GetMousePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*m_Window);
    return sf::Vector2f(mousePos.x, mousePos.y);
}

Application::Application()
{
    if (!InitWindow())
    {
        std::cerr << "Error in Initializing the window\n";
        exit(1);
    }

    if (!InitAppStates())
    {
        std::cerr << "Error in initializing the states\n";
        exit(1);
    }
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
    if (m_CurrentTest != m_TestMenu)
        delete m_CurrentTest;
    delete m_TestMenu;
}

bool Application::InitWindow()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    m_Window = new sf::RenderWindow(sf::VideoMode(s_WindowRes.x, s_WindowRes.y), "QuadTree Sim", sf::Style::Titlebar, settings);
    if (m_Window == nullptr)
    {
        std::cerr << "Couldn't Initialize Window!\n";
        return false;
    }
    m_View.setSize(s_WindowRes.x, s_WindowRes.y);                             // making the size as the resolution of the simulation
    m_View.setCenter(sf::Vector2f(s_WindowRes.x / 2.f, s_WindowRes.y / 2.f)); // making the center 0 and 0

    ImGui::SFML::Init(*m_Window, true);
    return true;
}

bool Application::InitAppStates()
{
    m_TestMenu = new TestMenu(m_CurrentTest);
    m_CurrentTest = m_TestMenu;

    m_TestMenu->RegisterTest<TestMouseAdding>("Test Adding with Mouse");
    m_TestMenu->RegisterTest<QuadTreeQueryTest>("Quad-Tree Query");
    return true;
}

void Application::HandleEvents()
{
    sf::Event event;
    while (m_Window->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            this->m_Window->close();
        m_CurrentTest->HandleEvents(event);
    }
}

void Application::Update(const sf::Time &dt)
{
    m_CurrentTest->Update(dt);
}

void Application::ImGuiUpdate(const sf::Time &dt)
{
    ImGui::SFML::Update(*m_Window, dt);
    if (m_CurrentTest != m_TestMenu && ImGui::Button("<-"))
    {
        delete m_CurrentTest;
        m_CurrentTest = m_TestMenu;
    }
    m_CurrentTest->OnImGuiRender();
}

void Application::Render()
{
    m_Window->setView(m_View);
    m_Window->clear();
    m_CurrentTest->Render(*m_Window);
    ImGui::SFML::Render(*m_Window);
    m_Window->display();
}