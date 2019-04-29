#pragma once
#include "Framework/GameObject.h"
#include <string>
using string = std::string;

class HUD: public GameObject
{
public:
	HUD();
	~HUD();

	void update(int, int, int, int, sf::RenderWindow*);

	void renderCount(sf::RenderWindow*);

private:
	sf::RectangleShape healthBar;
	sf::RectangleShape armourBar;
	sf::Text ammoCount;

	int health;
	int armour;
	int currentammo;
	int weaponammo;
	float scale;
	string ammoText;
	sf::Font ammoFont;
};


