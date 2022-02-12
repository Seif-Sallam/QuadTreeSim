#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
    sf::RectangleShape m_Shape;
    bool m_IsColliding;

public:
    Particle() = default;
    Particle(const sf::Vector2f &position, const sf::Vector2f &size);
    void Render(sf::RenderWindow &window);
    const sf::Vector2f GetPosition() const;
    const sf::Vector2f GetSize() const;
    const sf::FloatRect GetBoundingBox() const;
    void RandomMove();
    bool IsColliding(const sf::FloatRect &other);

private:
    void Highlight();
};