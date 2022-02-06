#include <iostream>
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>

const sf::Vector2u g_WindowRes = sf::Vector2u(800, 600);
int main()
{
    sf::RenderWindow window(sf::VideoMode(g_WindowRes.x, g_WindowRes.y), "Quad Tree Simulation", sf::Style::Titlebar);
    ImGui::SFML::Init(window);
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape)
                window.close();
        }
        ImGui::SFML::Update(window, dt);
        {
            ImGui::Begin("Test Window");
            ImGui::TextUnformatted("Hello, World!");

            ImGui::End();
            //ImGui Window
        }

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }
    return 0;
}
