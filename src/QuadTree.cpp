// #define DEBUG_ENABLED
#include "Globals.h"
#include "QuadTree.h"

QuadTree::QuadTree(const sf::FloatRect &boundry)
    : m_Boundry(boundry)
{
    for (auto &point : points)
        point = nullptr;
}

bool QuadTree::Insert(Particle *particle)
{
    if (particle)
    {
        sf::Vector2f point = particle->GetPosition();
        if (!m_Boundry.contains(point))
            return false;
        if (m_NumberOfElements < 4)
        {
            points[m_NumberOfElements] = particle;
            m_NumberOfElements++;
            return true;
        }
        else
        {
            if (!m_Divided)
                SubDivide();
        }
        if (this->m_NorthEast->Insert(particle))
        {
            LOG("Inserted North East\n");
            return true;
        }
        if (this->m_NorthWest->Insert(particle))
        {
            LOG("Inserted North West\n");
            return true;
        }
        if (this->m_SouthEast->Insert(particle))
        {
            LOG("Inserted South East\n");
            return true;
        }
        if (this->m_SouthWest->Insert(particle))
        {
            LOG("Inserted South West\n");
            return true;
        }
    }
    return false;
}

void QuadTree::SubDivide()
{
    float x = m_Boundry.left;
    float y = m_Boundry.top;
    float h = m_Boundry.height;
    float w = m_Boundry.width;
    sf::FloatRect nw = sf::FloatRect(x, y, w / 2.0f, h / 2.0f);
    sf::FloatRect ne = sf::FloatRect(x + w / 2.0f, y, w / 2.0f, h / 2.0f);
    sf::FloatRect se = sf::FloatRect(x + w / 2.0f, y + h / 2.0f, w / 2.0f, h / 2.0f);
    sf::FloatRect sw = sf::FloatRect(x, y + h / 2.0f, w / 2.0f, h / 2.0f);

    this->m_NorthWest = new QuadTree(nw);
    this->m_NorthEast = new QuadTree(ne);
    this->m_SouthWest = new QuadTree(sw);
    this->m_SouthEast = new QuadTree(se);
    m_Divided = true;
}

void QuadTree::Render(sf::RenderWindow &window)
{
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::White);
    shape.setPosition(m_Boundry.left, m_Boundry.top);
    shape.setSize(sf::Vector2f(m_Boundry.width, m_Boundry.height));
    window.draw(shape);
    for (int i = 0; i < points.size(); i++)
    {
        if (points[i] != nullptr)
            points[i]->Render(window);
    }
    if (m_Divided)
    {
        this->m_NorthEast->Render(window);
        this->m_NorthWest->Render(window);
        this->m_SouthEast->Render(window);
        this->m_SouthWest->Render(window);
    }
}

void QuadTree::Clean()
{
    if (m_Divided)
    {
        m_NorthEast->Clean();
        delete m_NorthEast;
        m_NorthWest->Clean();
        delete m_NorthWest;
        m_SouthEast->Clean();
        delete m_SouthEast;
        m_SouthWest->Clean();
        delete m_SouthWest;
        m_Divided = false;
    }
    for (int i = 0; i < points.size(); i++)
        points[i] = nullptr;
}

QuadTree::~QuadTree()
{
    Clean();
}