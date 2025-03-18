#pragma once
#include <SFML/Graphics.hpp>

#include <random>

class Game;

class Soggy
{
public:
	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window);

	void init(sf::Texture& m_sogTexture);

private:

	void spawn();

	int randomInt(int min, int max);

	float randomFloat(float min, float max);

	sf::RectangleShape m_sogSprite;

	int m_randomSogSize = 0;
	int m_sogSizeX = 0;
	int m_sogSizeY = 0;

	int m_sogRotationSpeedFactor = 1;
	int m_sogSpeedXFactor = 0.;
	int m_sogSpeedYFactor = 0;

	int m_sogRotationSpeed = 1.f;
	int m_sogSpeedX = 1.f;
	int m_sogSpeedY = 1.f;

	std::random_device rd;

	sf::Clock m_mitosisTimer;
	float m_mitosisRandom = 0.f;
};