#include "Particle.h"
#include "Random.h"
#include "Application.h"

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

void Particle::RandomMove()
{
    sf::Vector2f dir;
    dir.x = Random::GetRandomFloat(-3.0f, 3.0f);
    dir.y = Random::GetRandomFloat(-3.0f, 3.0f);
    sf::Vector2u windowRes = Application::GetWindowRes();
    m_Shape.move(dir);
    if (m_Shape.getPosition().x > windowRes.x - 5.f)
        m_Shape.setPosition(5.0f, m_Shape.getPosition().y);
    if (m_Shape.getPosition().x < 5.0f)
        m_Shape.setPosition(windowRes.x - 5.0f, m_Shape.getPosition().y);
    if (m_Shape.getPosition().y > windowRes.y - 5.f)
        m_Shape.setPosition(m_Shape.getPosition().x, 5.0f);
    if (m_Shape.getPosition().y < 5.0f)
        m_Shape.setPosition(m_Shape.getPosition().x, windowRes.y - 5.0f);
}

bool Particle::IsColliding(const sf::FloatRect &other)
{
    m_IsColliding = m_Shape.getLocalBounds().intersects(other);
    Highlight();
    return m_IsColliding;
}

void Particle::Highlight()
{
    int color = (m_IsColliding) ? 255 : 125;
    m_Shape.setFillColor(sf::Color(color, color, color, 255));
}