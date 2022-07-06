#include "Particle.h"
#include "Random.h"
#include "Application.h"

Particle::Particle(const sf::Vector2f &position, const sf::Vector2f &size)
{
    m_Shape.setPosition(position);
    m_Shape.setRadius(size.x / 2.0f);
    m_OriginalSize = size;
    m_Shape.setFillColor(sf::Color::White);
    m_HighlightOnce = false;
}

void Particle::Render(sf::RenderWindow &window)
{
    if (m_HighlightOnce)
    {
        m_Shape.setRadius(m_OriginalSize.x / 2.0f + 2.0f);
        m_Shape.setFillColor(sf::Color::Green);
        m_HighlightOnce = false;
    }
    else
    {
        m_Shape.setRadius(m_OriginalSize.x / 2.0f);
        m_Shape.setFillColor(sf::Color::White);
    }
    window.draw(m_Shape);
}

const sf::Vector2f Particle::GetPosition() const
{
    return m_Shape.getPosition();
}

const float Particle::GetSize() const
{
    return m_Shape.getRadius();
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
    if (m_Shape.getPosition().x > windowRes.x - 10.f)
        m_Shape.setPosition(5.0f, m_Shape.getPosition().y);
    if (m_Shape.getPosition().x < 5.0f)
        m_Shape.setPosition(windowRes.x - 10.0f, m_Shape.getPosition().y);
    if (m_Shape.getPosition().y > windowRes.y - 10.f)
        m_Shape.setPosition(m_Shape.getPosition().x, 5.0f);
    if (m_Shape.getPosition().y < 5.0f)
        m_Shape.setPosition(m_Shape.getPosition().x, windowRes.y - 10.0f);
}

bool Particle::IsColliding(const sf::FloatRect &other)
{
    m_IsColliding = m_Shape.getLocalBounds().intersects(other);
    return m_IsColliding;
}

void Particle::HighlightOnce()
{
    m_HighlightOnce = true;
}