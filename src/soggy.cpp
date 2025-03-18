#include "soggy.h"

void Soggy::update(sf::Int32 deltaMS)
{
    m_sogSprite.setRotation(m_sogSprite.getRotation() + m_sogRotationSpeed * m_sogRotationSpeedFactor);

    if (m_sogSprite.getRotation() >= 360)
        m_sogSprite.setRotation(0);
    else if (m_sogSprite.getRotation() <= 0)
        m_sogSprite.setRotation(0);

    m_sogSprite.setPosition(m_sogSprite.getPosition().x + m_sogSpeedX * m_sogSpeedXFactor, m_sogSprite.getPosition().y + m_sogSpeedY * m_sogSpeedYFactor);

    if ((m_sogSprite.getPosition().x >= 1920 && m_sogSpeedXFactor > 0) || (m_sogSprite.getPosition().x <= 0 && m_sogSpeedXFactor < 0))
    {
        m_sogSpeedXFactor *= -1;
        m_sogSpeedX += 0.05f;
        m_sogSpeedY += 0.05f;
        m_sogRotationSpeed += 0.1;
    }
    if ((m_sogSprite.getPosition().y >= 1080 && m_sogSpeedYFactor > 0) || (m_sogSprite.getPosition().y <= 0 && m_sogSpeedYFactor < 0))
    {
        m_sogSpeedYFactor *= -1;
        m_sogSpeedX += 0.05f;
        m_sogSpeedY += 0.05f;
        m_sogRotationSpeed += 0.1;
    }
}

void Soggy::render(sf::RenderWindow& window)
{
	window.draw(m_sogSprite);
}

void Soggy::init()
{
	m_sogTexture.loadFromFile("../sprites/soggycat.png");
	m_sogSprite.setTexture(&m_sogTexture);

    spawn();
}

void Soggy::spawn()
{
    m_randomSogSize = randomInt(1, 5);
    m_sogSizeX = 96.f * m_randomSogSize;
    m_sogSizeY = 128.f * m_randomSogSize;
    m_sogRotationSpeedFactor = 6 - m_randomSogSize;
    m_sogSpeedXFactor = 6 - m_randomSogSize;
    m_sogSpeedYFactor = m_sogSpeedXFactor;

    if (randomInt(0, 1) == 0)
        m_sogSpeedXFactor *= -1;
    if (randomInt(0, 1) == 0)
        m_sogSpeedYFactor *= -1;


    m_sogSprite.setOrigin(sf::Vector2f(m_sogSizeX / 2, m_sogSizeY / 2));
    m_sogSprite.setSize(sf::Vector2f(m_sogSizeX, m_sogSizeY));
    m_sogSprite.setRotation(randomInt(0, 359));
    m_sogSprite.setPosition(sf::Vector2f(randomInt(0, 1920), randomInt(0, 1080)));

    if (randomInt(0, 1) == 0)
        m_sogRotationSpeedFactor = -1;
}

int Soggy::randomInt(int min, int max)
{
    if (min > max)
    {
        int old = min;
        min = max;
        max = old;
    }
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}