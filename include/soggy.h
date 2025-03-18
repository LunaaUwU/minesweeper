#pragma once
#include <SFML/Graphics.hpp>

#include <random>

class Soggy
{
public:
	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window);

	void init();

private:

	void spawn();

	int randomInt(int min, int max);

	sf::RectangleShape m_sogSprite;
	sf::Texture m_sogTexture;
	int m_randomSogSize = 0;
	int m_sogSizeX = 0;
	int m_sogSizeY = 0;

	std::random_device rd;
};