#include <tileset.h>

void Tileset::update(sf::Int32 deltaMS)
{

}

void Tileset::render(sf::RenderWindow& window)
{
	
}

void Tileset::init(int numberToInstantiate)
{
	// Instanciar el máximo necesario (por ejemplo, si la dificultad dificil es 10x10, instanciar 100 y luego usar esas durante el resto de la partida, activando y desactivandolas
	for (int i = 0; i < numberToInstantiate; i++)
	{
		m_tileArray.push_back(new Tile());
	}
}

void Tileset::restart()
{

}

