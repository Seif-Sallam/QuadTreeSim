// #define DEBUG_ENABLED
#include "Globals.h"
#include "QuadTree.h"

QuadTree::QuadTree(const sf::FloatRect &boundry)
    : m_Boundry(boundry)
{
    for (auto &point : m_Points)
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
            m_Points[m_NumberOfElements] = particle;
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

void QuadTree::Render(sf::RenderWindow &window, bool renderPoints)
{
    sf::RectangleShape shape;
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::White);
    shape.setPosition(m_Boundry.left, m_Boundry.top);
    shape.setSize(sf::Vector2f(m_Boundry.width, m_Boundry.height));
    window.draw(shape);
    if (renderPoints)
        for (int i = 0; i < m_Points.size(); i++)
        {
            if (m_Points[i] != nullptr)
                m_Points[i]->Render(window);
        }
    if (m_Divided)
    {
        this->m_NorthEast->Render(window, renderPoints);
        this->m_NorthWest->Render(window, renderPoints);
        this->m_SouthEast->Render(window, renderPoints);
        this->m_SouthWest->Render(window, renderPoints);
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
    for (int i = 0; i < m_Points.size(); i++)
        m_Points[i] = nullptr;
}

QuadTree::~QuadTree()
{
    Clean();
}

void QuadTree::Query(const sf::FloatRect &range, std::vector<Particle *> &foundParticles, int *count)
{
    if (!this->m_Boundry.intersects(range))
        return;
    for (int i = 0; i < m_Points.size(); i++)
    {
        if (m_Points[i] != nullptr)
        {
            if (count != nullptr)
                *count = *count + 1;

            if (range.contains(m_Points[i]->GetPosition()))
                foundParticles.push_back(m_Points[i]);
        }
    }

    if (m_Divided)
    {
        m_NorthEast->Query(range, foundParticles, count);
        m_NorthWest->Query(range, foundParticles, count);
        m_SouthEast->Query(range, foundParticles, count);
        m_SouthWest->Query(range, foundParticles, count);
    }
}