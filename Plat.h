#pragma once
#include "Framework\GameObject.h"

class Plat : public GameObject
{
public:
	

	Plat();
	~Plat();
	
	void update();
private:
	sf::Texture platformTexture;
	float topSide;
	float bottomSide;
	float rightSide;
	float leftSide;

};