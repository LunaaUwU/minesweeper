#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <random>

class Game;

class Soggy
{
public:
	void update(sf::Int32 deltaMS);

	void render(sf::RenderWindow& window);

	void init(sf::Texture& sogTexture, sf::Texture& explosionTexture, sf::SoundBuffer& explosionSoundBuffer, int sogSize, int posX, int posY, float rot,
		float rotFact, float speedXFact, float speedYFact, float speedX, float speedY, float rotSpeed);

	int getSize() { return m_sogSize; }

	bool getActive() { return m_isActive; }

	void pauseSound();

	void resumeSound();

private:

	void spawn(int sogSize, int posX, int posY, float rot,
		float rotFact, float speedXFact, float speedYFact, float speedX, float speedY, float rotSpeed);

	int randomInt(int min, int max);

	float randomFloat(float min, float max);

	void changeSize(int size);

	void mitose();

	sf::RectangleShape m_sogSprite;

	bool m_isActive = true;
	bool m_isExploding = false;
	bool m_doOnce = false;
	bool m_lastExplosion = false;

	int m_sogSize = 0;
	int m_sogSizeX = 0;
	int m_sogSizeY = 0;

	int m_sogRotationSpeedFactor = 1;
	int m_sogSpeedXFactor = 0.;
	int m_sogSpeedYFactor = 0;

	float m_sogRotationSpeed = 1.f;
	float m_sogSpeedX = 1.f;
	float m_sogSpeedY = 1.f;

	sf::RectangleShape m_explosion;
	sf::Sound m_explosionSound;

	sf::Clock m_explosionAnimTimer;
	sf::Clock m_explosionTimer;
	int m_explosionColumn = 0;
	int m_explosionRow = 0;

	int m_explosionWidth = 71;
	int m_explosionHeight = 100;

	std::random_device rd;
};