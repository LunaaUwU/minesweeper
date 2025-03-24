#include "soggy.h"

#include "game.h"

void Soggy::update(sf::Int32 deltaMS)
{
    if (m_isActive)
    {
        m_sogSprite.setRotation(m_sogSprite.getRotation() + m_sogRotationSpeed * m_sogRotationSpeedFactor * deltaMS);

        if (m_sogSprite.getRotation() >= 360)
            m_sogSprite.setRotation(0);
        else if (m_sogSprite.getRotation() <= 0)
            m_sogSprite.setRotation(0);

        m_sogSprite.setPosition(m_sogSprite.getPosition().x + m_sogSpeedX * m_sogSpeedXFactor * deltaMS, m_sogSprite.getPosition().y + m_sogSpeedY * m_sogSpeedYFactor * deltaMS);

        if ((m_sogSprite.getPosition().x >= 1920 && m_sogSpeedXFactor > 0) || (m_sogSprite.getPosition().x <= 0 && m_sogSpeedXFactor < 0))
        {
            m_sogSpeedXFactor *= -1;
            m_sogSpeedX += 0.05f;
            m_sogSpeedY += 0.05f;
            m_sogRotationSpeed += 0.01f;

            if (randomInt(0, 10) == 0)
            {
                if (m_sogSize > 1)
                    mitose();
                else
                {
                    m_isActive = false;
                }
            }
        }
        if ((m_sogSprite.getPosition().y >= 1080 && m_sogSpeedYFactor > 0) || (m_sogSprite.getPosition().y <= 0 && m_sogSpeedYFactor < 0))
        {
            m_sogSpeedYFactor *= -1;
            m_sogSpeedX += 0.05f;
            m_sogSpeedY += 0.05f;
            m_sogRotationSpeed += 0.01f;

            if (randomInt(0, 10) == 0)
            {
                if (m_sogSize > 1)
                    mitose();
                else
                {
                    m_isActive = false;
                }
            }
        }
    }
}

void Soggy::render(sf::RenderWindow& window)
{
    if(m_isActive)
	    window.draw(m_sogSprite);
}

void Soggy::init(sf::Texture& m_sogTexture, int sogSize, int posX, int posY, float rot,
    float rotFact, float speedXFact, float speedYFact, float speedX, float speedY, float rotSpeed)
{
	m_sogSprite.setTexture(&m_sogTexture);
    spawn(sogSize, posX, posY, rot, rotFact, speedXFact, speedYFact, speedX, speedY, rotSpeed);
}

void Soggy::spawn(int sogSize, int posX, int posY, float rot,
    float rotFact, float speedXFact, float speedYFact, float speedX, float speedY, float rotSpeed)
{
    if (sogSize == 0)
        m_sogSize = randomInt(1, 5);
    else
        m_sogSize = sogSize;

    m_sogSizeX = 96.f * m_sogSize;
    m_sogSizeY = 128.f * m_sogSize;

    if (speedX == 0 && speedY == 0)
    {
        m_sogSpeedX = 6 - m_sogSize;
        m_sogSpeedY = 6 - m_sogSize;
        m_sogSpeedX /= 4;
        m_sogSpeedY /= 4;
    }
    else
    {
        m_sogSpeedX = speedX;
        m_sogSpeedY = speedY;

    }
    if (rotSpeed == 0)
    {
        m_sogRotationSpeed = 6 - m_sogSize;
        m_sogRotationSpeed /= 8;
    }
    else
        m_sogRotationSpeed = rotSpeed;

    if (speedXFact == 0 && speedYFact == 0)
    {
        m_sogSpeedXFactor = 1;
        m_sogSpeedYFactor = 1;
        if (randomInt(0, 1) == 0)
            m_sogSpeedXFactor *= -1;
        if (randomInt(0, 1) == 0)
            m_sogSpeedYFactor *= -1;
    }
    else
    {
        m_sogSpeedXFactor = speedXFact;
        m_sogSpeedYFactor = speedYFact;
    }

    m_sogSprite.setOrigin(sf::Vector2f(m_sogSizeX / 2, m_sogSizeY / 2));
    m_sogSprite.setSize(sf::Vector2f(m_sogSizeX, m_sogSizeY));

    if(posX == 0 && posY == 0)
        m_sogSprite.setPosition(sf::Vector2f(randomInt(0, 1920), randomInt(0, 1080)));
    else
        m_sogSprite.setPosition(sf::Vector2f(posX, posY));

    if(rot == -1)
        m_sogSprite.setRotation(randomInt(0, 359));
    else
        m_sogSprite.setRotation(rot);

    if (rotFact == 0)
    {
        if (randomInt(0, 1) == 0)
            m_sogRotationSpeedFactor = -1;
        else
            m_sogRotationSpeedFactor = 1;
    }
    
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

float Soggy::randomFloat(float min, float max)
{
    if (min > max)
    {
        float old = min;
        min = max;
        max = old;
    }
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

void Soggy::changeSize(int size)
{
    m_sogSize = size;
    m_sogSizeX = 96.f * m_sogSize;
    m_sogSizeY = 128.f * m_sogSize;
    m_sogSprite.setOrigin(sf::Vector2f(m_sogSizeX / 2, m_sogSizeY / 2));
    m_sogSprite.setSize(sf::Vector2f(m_sogSizeX, m_sogSizeY));
}

void Soggy::mitose()
{
    Game::shouldSpawnSog = true;
    Game::nextSogSize = m_sogSize - 1;
    Game::nextSogPos = m_sogSprite.getPosition();
    Game::nextSogRot = m_sogSprite.getRotation();
    Game::nextSogRotFact = (m_sogRotationSpeedFactor * -1);
    Game::nextSogSpeedFact = sf::Vector2f((m_sogSpeedXFactor * -1), (m_sogSpeedYFactor * -1));
    changeSize(m_sogSize - 1);
}

