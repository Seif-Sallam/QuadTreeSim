#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle() = default;
    Particle(const sf::Vector2f &position, const sf::Vector2f &size);
    void Render(sf::RenderWindow &window);
    const sf::Vector2f GetPosition() const;
    const float GetSize() const;
    const sf::FloatRect GetBoundingBox() const;
    void RandomMove();
    bool IsColliding(const sf::FloatRect &other);
    void HighlightOnce();

private:
    sf::CircleShape m_Shape;
    bool m_IsColliding;
    bool m_HighlightOnce;
    sf::Vector2f m_OriginalSize;
};