// #include <iostream>
// #include <imgui.h>
// #include <imgui-SFML.h>
// #include <Random.h>
// #include <SFML/Graphics.hpp>
// #include "Particle.h"
// #include "QuadTree.h"
// const sf::Vector2u g_WindowRes = sf::Vector2u(800, 600);
// /*
//     We want to create particles and each particle will be moving around the screen,
//     it will be highlighted if it collides with another particle (AABB) check
//     A particle is considered a Rectangle Shape and not a Circle Shape just to make it a little easier.
// */

// sf::Vector2f GenerateRandomV2f(const sf::Vector2f &min, const sf::Vector2f &max);

// int main()
// {

//     sf::FloatRect rect;
//     sf::RenderWindow window(sf::VideoMode(g_WindowRes.x, g_WindowRes.y), "Quad Tree Simulation", sf::Style::Titlebar);
//     ImGui::SFML::Init(window);
//     sf::Clock clock;
//     const int numberOfParticles = 10000;
//     std::array<Particle *, numberOfParticles> particles;
//     const sf::Vector2f particleSize = sf::Vector2f(1.f, 1.f);
//     QuadTree qt(sf::FloatRect(5, 5, g_WindowRes.x - 10.f, g_WindowRes.y - 10.f));
//     for (int i = 0; i < numberOfParticles; i++)
//     {
//         particles[i] = nullptr;
//         // particles[i] = new Particle(GenerateRandomV2f(sf::Vector2f(0.f, 0.f), sf::Vector2f(g_WindowRes.x, g_WindowRes.y)), particleSize);
//         // qt.Insert(particles[i]->GetPosition());
//     }
//     int index = 0;

//     while (window.isOpen())
//     {
//         sf::Time dt = clock.restart();
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             ImGui::SFML::ProcessEvent(event);

//             if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
//                 window.close();
//         }
//         static bool renderPoints = true;
//         static bool addWithMouse = false;
//         ImGui::SFML::Update(window, dt);
//         {
//             ImGui::Begin("Test Window");
//             ImGui::Text("Current Number Of Particles %d", index);
//             ImGui::Checkbox("Render Points", &renderPoints);
//             ImGui::Checkbox("Add With Mouse", &addWithMouse);
//             if (ImGui::Button("Add Particle") && index < numberOfParticles)
//             {
//                 sf::Vector2f position = GenerateRandomV2f(sf::Vector2f(0.f, 0.f), sf::Vector2f(g_WindowRes.x, g_WindowRes.y));
//                 particles[index] = new Particle(position, particleSize);
//                 qt.Insert(particles[index]);
//                 index++;
//             }
//             if (ImGui::Button("Add 10 Particles") && index < numberOfParticles)
//             {
//                 for (int i = 0; i < 10 && index < numberOfParticles; i++)
//                 {
//                     sf::Vector2f position = GenerateRandomV2f(sf::Vector2f(0.f, 0.f), sf::Vector2f(g_WindowRes.x, g_WindowRes.y));
//                     particles[index] = new Particle(position, particleSize);
//                     qt.Insert(particles[index]);
//                     index++;
//                 }
//             }

//             ImGui::End();
//         }
//         if (addWithMouse)
//         {
//             if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//             {
//                 sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
//                 sf::Vector2f position = GenerateRandomV2f(mousePosition, sf::Vector2f(mousePosition.x + rand() % 10, mousePosition.y + rand() % 10));

//                 particles[index] = new Particle(position, particleSize);
//                 qt.Insert(particles[index]);
//                 index++;
//             }
//         }
//         window.clear();
//         ImGui::SFML::Render(window);
//         qt.Render(window, renderPoints);
//         window.display();
//     }
//     for (int i = 0; i < numberOfParticles; i++)
//         delete particles[i];

//     return 0;
// }

// sf::Vector2f GenerateRandomV2f(const sf::Vector2f &min, const sf::Vector2f &max)
// {
//     return sf::Vector2f(Random::GetRandomFloat(min.x, max.x), Random::GetRandomFloat(min.y, max.y));
// }

#include "Application.h"

int main()
{
    Application app;
    app.Run();
    return 0;
}
