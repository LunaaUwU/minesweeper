#include "soggy.h"

void Soggy::update(sf::Int32 deltaMS)
{
    m_sogSprite.setRotation(m_sogSprite.getRotation() + 1);
    if (m_sogSprite.getRotation() >= 360)
        m_sogSprite.setRotation(0);
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
    m_sogSprite.setOrigin(sf::Vector2f(m_sogSizeX / 2, m_sogSizeY / 2));
    m_sogSprite.setSize(sf::Vector2f(m_sogSizeX, m_sogSizeY));
    m_sogSprite.setRotation(randomInt(0, 359));
    m_sogSprite.setPosition(sf::Vector2f(randomInt(0, 1920), randomInt(0, 1080)));
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