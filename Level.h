#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/TileMap.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Plat.h"
#include "Pickups.h"
#include "HUD.h"


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

	void loadFoesandPlats();
	
private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::Texture backgroundTexture;
	sf::Texture hudTexture;
	sf::RenderWindow* window;
	sf::Sprite Background;
	sf::View view1;
	sf::View hudView;
	sf::Vector2f position;
	sf::Vector2i pixelpos;
	sf::Vector2f mappos;
	Input* input;
	Player player;
	Enemy foe;
	std::vector<Enemy> enemy;
	GameState* gameState;
	AudioManager* audio;
	std::vector<Plat> platform;
	Plat plat;
	std::vector<Pickups> pickups;
	HUD hud;
};