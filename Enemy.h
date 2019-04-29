#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Vector.h"
#include "Framework/Animation.h"
#include "Arms.h"

class Enemy : public GameObject
{
public:
	//constructor/deconstructor
	Enemy();
	~Enemy();

	//Getters and Setters
	int getHealth();
	
	void setGuntype(int);
	void setHealth(int);

	//functions
	void initEnemy();
	void update(float, sf::RenderWindow*, sf::Vector2f);
	void playerCheck(float, sf::Vector2f);
	void maxSpeed(float);
	void wallBoundries(sf::RenderWindow*);
	void renderArm(sf::RenderWindow* );
	void shoot();
	void changeWeapon();
	void bulletCollision(sf::FloatRect, int);
	std::vector<Bullet>& getBullets();
	



protected:
	Arms Earm = Arms(2);
	Animation* currentAnimation;
	Animation walk;
	Animation crouch;
	Animation idle;
	sf::Texture enemyTexture;
	sf::Clock fireRateClock;
	sf::Clock shootingTimeClock;
	sf::Time fireRate;
	sf::Time shootingTime;
	sf::Time firedTime;
	sf::Time timetoshoot;
	sf::Time timetocool;
	int gunType;
	int health;
	bool fired;
	bool is_jumping;
	bool follow;
	float scale;
	float acceleration;
	float deceleration;
	float jump_force;
	float max_speed;
	float gravity;
	float arm_rotation;
	float distance;



};