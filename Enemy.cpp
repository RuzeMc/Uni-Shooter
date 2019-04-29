#include "Enemy.h"
#include <iostream>

//constructor and deconstructor
Enemy::Enemy()
{
	initEnemy();
	setPosition(600, 0);
	velocity = sf::Vector2f(0, 0);
	health = 100;
	scale = 200.f;
	acceleration = 1.f;
	deceleration = 1.f;
	jump_force = 2.5f;
	max_speed = 125.f;
	gravity = 9.8f;
	is_jumping = true;
	follow = false;
	setAlive(false);
	gunType = 1;
	fireRate = sf::seconds(0.5);
	timetoshoot = sf::seconds(5);
	timetocool = sf::seconds(8);
}
Enemy::~Enemy() {}

//getters and setters

int Enemy::getHealth()
{
	return health;
}

void Enemy::setHealth(int n)
{
	health = health - n;
}

void Enemy::setGuntype(int n)
{
	gunType = n;
}

//Functions


void Enemy::update(float dt, sf::RenderWindow* window, sf::Vector2f playerPos)
{

	Earm.update(dt, playerPos, getPosition(), window);
	firedTime = fireRateClock.getElapsedTime();
	shootingTime = shootingTimeClock.getElapsedTime();

	wallBoundries(window);
	setTextureRect(currentAnimation->getCurrentFrame());
	playerCheck(dt, playerPos);

	if (firedTime.asSeconds() >= fireRate.asSeconds())
	{
		fired = false;
	}

	if (shootingTime.asSeconds() >= timetocool.asSeconds())
	{
		shootingTimeClock.restart();
	}

	if (getPosition().x < 6000)
	{
		setGuntype(1);
	}
	else if (getPosition().x > 6000 && getPosition().x < 12000)
	{
		setGuntype(2);
	}
	else if (getPosition().x > 12000 && getPosition().x < 18000)
	{
		setGuntype(3);
	}

	if (health <= 0)
	{
		setAlive(false);
	}
	
	changeWeapon();

}

void Enemy::initEnemy()
{
	enemyTexture.loadFromFile("gfx/Enemy_and_Arm.png");
	setTexture(&enemyTexture);

	idle.addFrame(sf::IntRect(0, 19, 18, 44));

	walk.addFrame(sf::IntRect(26, 19, 21, 43));
	walk.addFrame(sf::IntRect(55, 19, 21, 43));
	walk.addFrame(sf::IntRect(86, 19, 25, 43));
	walk.setFrameSpeed(1.f / 10.f);

	crouch.addFrame(sf::IntRect(113, 30, 26, 33));

	currentAnimation = &idle;
	setSize(sf::Vector2f(36, 88));
}

void Enemy::maxSpeed(float speed)
{
	if (speed >= max_speed)
	{
		velocity.x = max_speed;
	}
	else if (speed <= -max_speed)
	{
		velocity.x = -max_speed;
	}
}



void Enemy::wallBoundries(sf::RenderWindow* window)
{
	if (this->getPosition().x <= 0)
	{
		currentAnimation = &idle;
		setSize(sf::Vector2f(36, 88));
		velocity.x = 0;
		this->setPosition(0, this->getPosition().y);
	}

	if (this->getPosition().y >= window->getSize().y - this->getSize().y)
	{
		setPosition(this->getPosition().x, window->getSize().y - this->getSize().y);
		velocity.y = 0;
		is_jumping = false;
	}
	
}

void Enemy::playerCheck(float dt, sf::Vector2f playerPos)
{
	if (playerPos.x >= getPosition().x - 500 && playerPos.x < getPosition().x)
	{
		
		currentAnimation->setFlipped(true);
		Earm.lookatTarget();
		shoot();
	}
	else if(playerPos.x <= getPosition().x + 500 && playerPos.x > getPosition().x)
	{
		currentAnimation->setFlipped(false);
		Earm.lookatTarget();
		shoot();
	}
	else
	{
		currentAnimation = &idle;
		setSize(sf::Vector2f(36, 88));
	}
}


void Enemy::shoot()
{
	
	if (!fired)
	{
		if (gunType < 3)
		{
			fireRateClock.restart();
			fired = true;
			Earm.createBullet();
		}
		else if (gunType == 3 && shootingTime.asSeconds() <= timetoshoot.asSeconds())
		{
			fireRateClock.restart();
			fired = true;
			Earm.createBullet();
		}
	}
}

void Enemy::changeWeapon()
{
	if (gunType == 1)
	{
		fireRate = sf::seconds(1);
		Earm.changeWeapon(1);
	}
	else if (gunType == 2)
	{
		fireRate = sf::seconds(2);
		Earm.changeWeapon(2);
	}
	else if(gunType == 3)
	{
		fireRate = sf::seconds(0.5);
		Earm.changeWeapon(3);
	}
}


void Enemy::renderArm(sf::RenderWindow* window)
{
	Earm.renderBullets(window);
	window->draw(Earm);
}

void Enemy::bulletCollision(sf::FloatRect bulletBox, int bulletType)
{
	sf::FloatRect enemyBox = getLocalBounds();
	
	if (bulletBox.intersects(enemyBox))
	{
		switch (bulletType)
		{
		case 1:
			health -= 34;
			break;
		case 2:
			health -= 15;
			break;
		case 3:
			health -= 66;
			break;
		}
	}
}

std::vector<Bullet>& Enemy::getBullets()
{
	return Earm.getBullets();
}
