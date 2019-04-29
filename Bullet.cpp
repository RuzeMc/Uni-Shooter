#include "Bullet.h"

Bullet::Bullet()
{
	initBullet();
	ammoType = 1;
	setAlive(false);
}
Bullet::~Bullet() {}



void Bullet::update(float dt, sf::RenderWindow* window)
{
	direction = Vector::normalise(direction);
	ammoSpeed = (bulletSpeed * direction);
	move(ammoSpeed*dt);
	wallBoundries(window);
}

void Bullet::movetoMouse(float rotation)
{
	this->setRotation(rotation);
}

void Bullet::setAmmoSpeed(int n)
{
	switch (n)
	{
	case 1:
		bulletSpeed = 450.f;
		break;
	case 2:
		bulletSpeed = 650.f;
		break;
	case 3:
		bulletSpeed = 550.f;
		break;
	}
}

void Bullet::wallBoundries(sf::RenderWindow* window)
{
	

	if (this->getPosition().x <= window->getView().getCenter().x - (window->getSize().x/2))
	{
		this->setAlive(false);
	}
	else if (this->getPosition().x >= window->getView().getCenter().x + (window->getSize().x / 2))
	{
		this->setAlive(false);
	}
	else if (this->getPosition().y < 0)
	{
		this->setAlive(false);
	}
	else if (this->getPosition().y > 600)
	{
		this->setAlive(false);
	}
}



void Bullet::initBullet()
{
	setSize(sf::Vector2f(5, 5));
}

void Bullet::setDirection(sf::Vector2f dir) { direction = dir; }

void Bullet::ammoSelection(int n)
{
	ammoType = n;
}

int Bullet::getammoType()
{
	return ammoType;
}