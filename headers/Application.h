#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>

class Application
{
public:
    Application();
    Application(Application &) = delete;
    void Run();
    static const sf::Vector2u GetWindowRes();
    ~Application();

private:
    bool InitWindow();
    bool InitAppStates();

    void HandleEvents();
    void Update(const sf::Time &dt);
    void ImGuiUpdate(const sf::Time &dt);
    void Render();

private:
    sf::RenderWindow *m_Window;
    sf::View m_View;
    static sf::Vector2u s_WindowRes;
    sf::Clock m_Clock;
};