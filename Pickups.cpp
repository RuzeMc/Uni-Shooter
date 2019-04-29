#include "Pickups.h"
#include <iostream>

Pickups::Pickups()
{
	textureSet = false;
	setAlive(true);
}

Pickups::~Pickups(){}

void Pickups::setObjectType(int n)
{
	objectType = n;
}

void Pickups::update(float dt)
{
}

void Pickups::collisions(sf::FloatRect playerBox)
{

}

void Pickups::IntitPickups(int n)
{
	
	switch (n)
	{
	case 1:
		setObjectType(n);
		boxTexture.loadFromFile("gfx/Pickups.png");
		setTexture(&boxTexture);
		setTextureRect(sf::IntRect(0, 0, 12, 12));
		setSize(sf::Vector2f(12, 12));
		textureSet = true;
		break;
	case 2:
		setObjectType(n);
		boxTexture.loadFromFile("gfx/Pickups.png");
		setTexture(&boxTexture);
		setTextureRect(sf::IntRect(34, 0, 15, 16));
		setSize(sf::Vector2f(15, 16));
		textureSet = true;
		break;
	case 3:
		setObjectType(n);
		boxTexture.loadFromFile("gfx/Pickups.png");
		setTexture(&boxTexture);
		setTextureRect(sf::IntRect(49, 0, 15, 16));
		setSize(sf::Vector2f(15, 16));
		textureSet = true;
		break;
	case 4:
		setObjectType(n);
		boxTexture.loadFromFile("gfx/Pickups.png");
		setTexture(&boxTexture);
		setTextureRect(sf::IntRect(13, 0, 20, 20));
		setSize(sf::Vector2f(20, 20));
		textureSet = true;
		break;
	case 5:
		setObjectType(n);
		boxTexture.loadFromFile("gfx/Pickups.png");
		setTexture(&boxTexture);
		setTextureRect(sf::IntRect(65, 0, 38, 20));
		setSize(sf::Vector2f(38, 20));
		textureSet = true;
		break;
	case 6:
		setObjectType(n);
		boxTexture.loadFromFile("gfx/Pickups.png");
		setTexture(&boxTexture);
		setTextureRect(sf::IntRect(104, 0, 48, 20));
		setSize(sf::Vector2f(48, 20));
		textureSet = true;
		break;
	}
}

bool Pickups::isSet()
{
	return textureSet;
}

void Pickups::setSet(bool b)
{
	textureSet = b;
}

int Pickups::getobjectType()
{
	return objectType;
}