#include "Particle.h"

Particle::Particle(const sf::Vector2f &position, const sf::Vector2f &size)
{
    m_Shape.setPosition(position);
    m_Shape.setSize(size);
    m_Shape.setFillColor(sf::Color::White);
}

void Particle::Render(sf::RenderWindow &window)
{
    window.draw(m_Shape);
}

const sf::Vector2f Particle::GetPosition() const
{
    return m_Shape.getPosition();
}

const sf::Vector2f Particle::GetSize() const
{
    return m_Shape.getSize();
}
const sf::FloatRect Particle::GetBoundingBox() const
{
    return m_Shape.getGlobalBounds();
}