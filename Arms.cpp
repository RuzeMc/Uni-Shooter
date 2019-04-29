#include "Arms.h"
#include <iostream>

//initalise Weapon Variables
Arms::Arms(int player)
{
	if (player == 1)
	{
		initPArms();
	}
	else
	{
		initEArms();
	}
	currentWeapon = 1;
	direction = sf::Vector2f(0, 0);
	flipped = false;
	this->setOrigin(4, 16);
	armPos = sf::Vector2f(8, 32);
}
Arms::~Arms() {}


void Arms::update(float dt, sf::Vector2f playerPos,sf::Vector2f enemyPos, sf::RenderWindow* window)
{

	
	setTextureRect(currentGun->getCurrentFrame());

	if (getRotation() > 90.f && getRotation() < 270.f)
	{
		if (currentGun == &Shotgun)
		{
			this->setOrigin(16, 24);
		}
		else
		{
			this->setOrigin(4, 16);
		}

		armPos = sf::Vector2f(32, 32);
		currentGun->setFlipped(false);
		sf::IntRect frame = currentGun->getCurrentFrame();
		currentGun->setFlipped(true);
		sf::IntRect frame2 = sf::IntRect(frame.left, frame.top + frame.height, frame.width, -frame.height);
		setTextureRect(frame2);
		setPosition(enemyPos + armPos);
	}
	else
	{
		if (currentGun == &Shotgun)
		{
			this->setOrigin(16, 8);
		}
		currentGun->setFlipped(false);
		armPos = sf::Vector2f(8, 32);

		//set arm to player's shoulder
		setPosition(enemyPos + armPos);
	}

	calcualteRadians(getRotation());
	//set arms to players position and rotate to mouse
	bulletPos.x = getPosition().x + 50 * cos(radians);
	bulletPos.y = getPosition().y + 50 * sin(radians);
	direction.x = playerPos.x - getPosition().x;
	direction.y = playerPos.y - getPosition().y + 20;
	
	//checking if bullet is alive and if so update it
	for (auto currentBullet = bullets.begin(); currentBullet != bullets.end();)
	{
		if (currentBullet->isAlive() == false)
			currentBullet = bullets.erase(currentBullet);
		else
		{
			currentBullet->update(dt, window);
			++currentBullet;
		}
	}
	
}

void Arms::update(float dt, sf::Vector2f playerPos, sf::RenderWindow* window)
{
	
	//set current frame for arm
	setTextureRect(currentGun->getCurrentFrame());

	if (getRotation() > 90.f && getRotation() < 270.f)
	{
		if (currentGun == &Shotgun)
		{
			this->setOrigin(16, 24);
		}
		else
		{
			this->setOrigin(4, 16);
		}

		armPos = sf::Vector2f(32, 32);
		currentGun->setFlipped(false);
		sf::IntRect frame = currentGun->getCurrentFrame();
		currentGun->setFlipped(true);
		sf::IntRect frame2 = sf::IntRect(frame.left, frame.top + frame.height, frame.width, -frame.height);
		setTextureRect(frame2);
		setPosition(playerPos + armPos);
	}
	else
	{
		if (currentGun == &Shotgun)
		{
			this->setOrigin(16, 8);
		}
		currentGun->setFlipped(false);
		armPos = sf::Vector2f(8, 32);

		//set arm to player's shoulder
		setPosition(playerPos + armPos);
	}

	calcualteRadians(getRotation());
	//set arms to players position and rotate to mouse
	sf::Vector2i pixelpos = sf::Vector2i(input->getMouseX(), input->getMouseY());
	sf::Vector2f worldpos = window->mapPixelToCoords(pixelpos);
	bulletPos.x = getPosition().x + 50 * cos(radians);
	bulletPos.y = getPosition().y + 50 * sin(radians) - 5;
	direction.x = worldpos.x  - getPosition().x;
	direction.y = worldpos.y - getPosition().y;
	lookatTarget();


	//checking if bullet is alive and if so update it
	for (auto currentBullet = bullets.begin(); currentBullet != bullets.end();)
	{
		if (currentBullet->isAlive() == false)
			currentBullet = bullets.erase(currentBullet);
		else
		{
			currentBullet->update(dt, window);
			++currentBullet;
		}
	}

}

//rotating arm to Target
void Arms::lookatTarget()
{
	const float PI = 3.14159265f;

	float rotation = (std::atan2(direction.y + 20, direction.x)) * 180 / PI;
	this->setRotation(rotation);
}

void Arms::calcualteRadians(float angle)
{
	float PI = 3.14159265f;
	radians = (angle * PI) / 180;
}


void Arms::renderBullets(sf::RenderWindow* window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		window->draw(bullets[i]);
	}
}

void Arms::createBullet()
{
	//instance a bullet and set values
	Bullet b;
	b.setFillColor(sf::Color(255,255,0,255));
	b.setAlive(true);
	b.setDirection(direction);
	b.setPosition(bulletPos);
	b.movetoMouse(getRotation());
	b.setAmmoSpeed(currentWeapon);

	//now add it to the bullets vector for it to be drawn, updated etc.
	if (currentGun == &Shotgun)
	{
		for (int i = 0; i < 5; i++)
		{
			if (currentGun->getFlipped())
			{
				b.setDirection(direction + sf::Vector2f(-i * 12.5, -i * 12.5));
			}
			else
			{
				b.setDirection(direction + sf::Vector2f(i* 12.5, i*12.5));
			}

			bullets.push_back(b);
		}
	}
	else
	{
		bullets.push_back(b);
	}

}
void Arms::initPArms()
{
	bulletTexture.loadFromFile("gfx/Pistol_Bullet.png");

	WeaponArm.loadFromFile("gfx/Player_and_Arm.png");
	setTexture(&WeaponArm);


	Pistol.addFrame(sf::IntRect(126, 1, 37, 16));
	Pistol.addFrame(sf::IntRect(126, 0, 49, 16));
	Pistol.setFrameSpeed(1.f / 200.f);


	Shotgun.addFrame(sf::IntRect(67, 1, 46, 14));
	Shotgun.addFrame(sf::IntRect(67, 0, 58, 17));
	Shotgun.setFrameSpeed(1.f / 2.f);

	AR.addFrame(sf::IntRect(0, 0, 54, 17));
	AR.addFrame(sf::IntRect(0, 0, 66, 17));
	AR.setFrameSpeed(1.f / 10.f);

	currentGun = &Pistol;
	setSize(sf::Vector2f(74, 32));
}


void Arms::initEArms()
{
	WeaponArm.loadFromFile("gfx/Enemy_and_Arm.png");
	setTexture(&WeaponArm);


	Pistol.addFrame(sf::IntRect(126, 1, 37, 16));
	Pistol.addFrame(sf::IntRect(126, 0, 49, 16));
	Pistol.setFrameSpeed(1.f / 200.f);


	Shotgun.addFrame(sf::IntRect(67, 1, 46, 14));
	Shotgun.addFrame(sf::IntRect(67, 0, 58, 17));
	Shotgun.setFrameSpeed(1.f / 2.f);

	AR.addFrame(sf::IntRect(0, 0, 54, 17));
	AR.addFrame(sf::IntRect(0, 0, 66, 17));
	AR.setFrameSpeed(1.f / 10.f);

	currentGun = &Pistol;
	setSize(sf::Vector2f(74, 32));
}

void Arms::changeWeapon(int i)
{
	currentWeapon = i;
	switch (currentWeapon)
	{
	case 1:
		currentGun = &Pistol;
		barrelPos = 11;
		this->setOrigin(4, 16);
		break;
	case 2:
		currentGun = &Shotgun;
		barrelPos = 0;
		this->setOrigin(16, 8);
		break;
	case 3:
		currentGun = &AR;
		barrelPos = 11;
		this->setOrigin(4, 16);
		break;
	}
	
}


std::vector<Bullet>& Arms::getBullets()
{
	return bullets;
}