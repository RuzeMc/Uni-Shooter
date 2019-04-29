#pragma once
#include "Framework/GameObject.h"

class Pickups : public GameObject
{
public:
	Pickups();
	~Pickups();
	void setSet(bool);
	void setObjectType(int);

	void IntitPickups(int);
	void update(float);
	void collisions(sf::FloatRect);
	bool isSet();

	int getobjectType();




private:
	sf::Texture boxTexture;
	int objectType;
	int health = 25;
	int armour;
	int ammo;
	int ammotype;
	bool textureSet;



};