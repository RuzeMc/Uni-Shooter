#pragma once
#include "Framework/GameObject.h"
#include "Framework/Vector.h"
#include "Framework/Animation.h"
#include "Bullet.h"
#include <vector>

class Arms : public GameObject
{
public:
	Arms(int);
	~Arms();

	void update(float, sf::Vector2f, sf::Vector2f, sf::RenderWindow*);
	void update(float, sf::Vector2f, sf::RenderWindow* );
	void lookatTarget();
	void renderBullets(sf::RenderWindow*);
	void calcualteRadians(float);
	void createBullet();
	void initPArms();
	void initEArms();
	void changeWeapon(int);
	std::vector<Bullet>& getBullets();

protected:
	Animation* currentGun;
	Animation Shotgun;
	Animation Pistol;
	Animation AR;
	sf::Texture bulletTexture;
	sf::Texture WeaponArm;
	std::vector<Bullet> bullets;
	sf::Vector2f direction;
	sf::Vector2f bulletPos;
	sf::Vector2f armPos;	
	int currentWeapon;
	bool flipped;
	bool player;
	float radians;
	float barrelPos;

};

