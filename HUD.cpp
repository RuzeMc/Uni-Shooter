#include "HUD.h"

HUD::HUD()
{
	setSize(sf::Vector2f(1200, 65));
	ammoText = "";
	scale = 0.8f;
	health = 100;
	armour = 0;
	healthBar.setFillColor(sf::Color(255, 0, 0));
	armourBar.setFillColor(sf::Color(0, 0, 255));
	ammoFont.loadFromFile("font/arial.ttf");
	ammoCount.setFont(ammoFont);
	ammoCount.setFillColor(sf::Color(255, 255, 0));
	ammoCount.setCharacterSize(18);
}

HUD::~HUD() {}

void HUD::update(int hp, int shield, int inGun, int Spare ,sf::RenderWindow* window)
{
	health = hp;
	armour = shield;
	ammoText = std::to_string(inGun) + " / " + std::to_string(Spare);
	ammoCount.setString(ammoText);
	ammoCount.setPosition(getPosition().x + (getSize().x *0.9),20);
	armourBar.setSize(sf::Vector2f(armour*scale, 25 * scale));
	armourBar.setPosition(getPosition().x + (getSize().x * 0.2) ,35);
	healthBar.setSize(sf::Vector2f(health*scale, 25 * scale));
	healthBar.setPosition(getPosition().x + (getSize().x * 0.05),35);
}

void HUD::renderCount(sf::RenderWindow* window)
{
	window->draw(ammoCount);
	window->draw(healthBar);
	window->draw(armourBar);
}