#pragma once
#include <iostream>
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Vector.h"
#include "Framework/Animation.h"
#include "Arms.h"
#include "Plat.h"

class Player : public GameObject
{
public:
	//constructor/destructor
	Player();
	~Player();
	
	//getters and setters
	void setClipSize(int);
	void setMaxAmmo(int);
	void setAmmo(int i);
	void setArmRotation(float);
	void setJumping(bool);
	int getHealth();
	int getArmour();
	int getWeaponAmmo(int);
	int getCurrentAmmo();
	int getSpareAmmo();


	//player functions
	void handleInput(float);
	void update(float, sf::RenderWindow*);
	void initPlayer();
	void reload();
	void slowDown(float);
	void wallBoundries(sf::RenderWindow* ,float);
	void maxSpeed(float);
	bool fullMag(int i);
	void renderArm(sf::RenderWindow*);
	void collisionResponse(sf::FloatRect, float );
	void pickupResponse(int);
	void bulletCollision(sf::FloatRect, int);


protected:
	Arms Parm = Arms(1);
	Animation* currentAnimation;
	Animation walk;
	Animation crouch;
	Animation idle;
	sf::Texture playerTexture;
	sf::Clock fireRateClock;
	sf::Clock reloadClock;
	sf::Time fireRate;
	sf::Time reloadRate;
	sf::Time firedTime;
	sf::Time reloadTime;
	int clip_size;
	int gunType;
	int health;
	int armour;
	int current_ammo;
	int max_ammo;
	int pistol_ammo;
	int shotgun_ammo;
	int ar_ammo;
	int current_pistol;
	int current_shotgun;
	int current_ar;
	bool fired;
	bool reloaded;
	bool moving;
	bool is_jumping;
	float scale;
	float acceleration;
	float deceleration;
	float jump_force;
	float max_speed;
	float gravity;
	float arm_rotation;
};
