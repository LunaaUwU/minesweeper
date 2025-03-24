#pragma once
#include <SFML/Graphics.hpp>

#include <random>

class Game;

class Soggy
{
public:
	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window);

	void init(sf::Texture& m_sogTexture, int sogSize, int posX, int posY, float rot,
		float rotFact, float speedXFact, float speedYFact);

private:

	void spawn(int sogSize, int posX, int posY, float rot,
		float rotFact, float speedXFact, float speedYFact);

	int randomInt(int min, int max);

	float randomFloat(float min, float max);

	void changeSize(int size);

	sf::RectangleShape m_sogSprite;

	int m_sogSize = 0;
	int m_sogSizeX = 0;
	int m_sogSizeY = 0;

	int m_sogRotationSpeedFactor = 1;
	int m_sogSpeedXFactor = 0.;
	int m_sogSpeedYFactor = 0;

	float m_sogRotationSpeed = 1.f;
	float m_sogSpeedX = 1.f;
	float m_sogSpeedY = 1.f;

	std::random_device rd;

	sf::Clock m_mitosisTimer;
	float m_mitosisRandom = 0.f;
};