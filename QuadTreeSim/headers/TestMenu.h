#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "imgui.h"

class Test
{
public:
    Test() = default;

    virtual ~Test() = default;

    inline virtual void Update(const sf::Time &dt) {}
    inline virtual void HandleEvents(const sf::Event &event) {}
    inline virtual void Render(sf::RenderWindow &window) {}
    inline virtual void OnImGuiRender() {}
};

class TestMenu : public Test
{
public:
    TestMenu(Test *&currentTest);
    void OnImGuiRender();
    template <typename T>
    void RegisterTest(const std::string &name)
    {
        m_Tests.push_back(std::make_pair(name, []()
                                         { return new T(); }));
    }

private:
    std::vector<std::pair<std::string, std::function<Test *()>>> m_Tests;
    Test *&m_CurrentTest;
};