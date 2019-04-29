#include "Plat.h"

Plat::Plat()
{
	platformTexture.loadFromFile("gfx/Tiles.png");
	setTexture(&platformTexture);
	setSize(sf::Vector2f(200, 50));
}

Plat::~Plat() {}

void Plat::update()
{
	topSide = getPosition().y;
	rightSide = getPosition().x + getLocalBounds().width;
	leftSide = getPosition().x;
	bottomSide = getPosition().y + getLocalBounds().height;
}