#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework\Animation.h"
#include "Framework/Vector.h"

class Bullet : public GameObject
{
public:
	Bullet();
	~Bullet();
	void ammoSelection(int);
	void update(float, sf::RenderWindow*);
	void movetoMouse(float);
	void setAmmoSpeed(int);
	void wallBoundries(sf::RenderWindow*);
	void initBullet();
	void setDirection(sf::Vector2f dir);
	int getammoType();
protected:
	int ammoType;
	sf::Vector2f ammoSpeed;
	sf::Vector2f direction;
	float bulletSpeed;
};