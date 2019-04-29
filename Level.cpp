#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	input->setMouseLDown(false);
	// initialise game objects
	view1.reset(sf::FloatRect(0, 0, 1200, window->getSize().y));
	view1.setViewport(sf::FloatRect(0, 0, 1.f,1.f));
	hudView.reset(sf::FloatRect(0, 0, 1200, 65));
	hudView.setViewport(sf::FloatRect(0, 0, 1.0f, 0.09f));
	
	backgroundTexture.loadFromFile("gfx/Background_v1.png");
	backgroundTexture.setRepeated(true);
	Background.setTexture(backgroundTexture);
	Background.setPosition(sf::Vector2f(0, 0));
	Background.setTextureRect(sf::IntRect(0, 0, 18000, 600));

	hudTexture.loadFromFile("gfx/HUD.png");
	hud.setTexture(&hudTexture);
	hud.setTextureRect(sf::IntRect(0, 0, 1200, 65));
	   
	plat.setPosition(300, window->getSize().y - 150);
	platform.push_back(plat);

	

	loadFoesandPlats();

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	player.setInput(input);
	player.handleInput(dt);

}

// Update game objects
void Level::update(float dt)
{
	

	hud.update(player.getHealth(), player.getArmour(), player.getCurrentAmmo(), player.getSpareAmmo(), window);
	hud.setPosition(mappos.x, mappos.y);
	
	for (int i = 0; i < platform.size(); i++)
	{
		if (platform[i].getPosition().x >= view1.getCenter().x - (view1.getSize().x / 2) &&	platform[i].getPosition().x 
			+ platform[i].getSize().x <= view1.getCenter().x + view1.getCenter().x + (view1.getSize().x /2))
		{
			platform[i].update();
			sf::FloatRect platformBox = platform[i].getGlobalBounds();
			player.collisionResponse(platformBox, dt);
		}
	}

	window->setSize(sf::Vector2u(1200, 600));
	position.x = (player.getPosition().x + (player.getSize().x / 2)) - (window->getSize().x / 2);
	player.update(dt, window);

	for (auto currentEnemy = enemy.begin(); currentEnemy != enemy.end();)
	{

		if (currentEnemy->isAlive() == false)
			currentEnemy = enemy.erase(currentEnemy);
		else 
		{
			currentEnemy->update(dt, window, player.getPosition());
		}
		currentEnemy++;
	}


	for (auto currentPickup = pickups.begin(); currentPickup != pickups.end();)
	{
		if (currentPickup->isAlive() == false)
			currentPickup = pickups.erase(currentPickup);
		else
		{
			if (!currentPickup->isSet())
			{
				currentPickup->IntitPickups(rand() % 6 + 1);
				currentPickup->setPosition(currentPickup->getPosition().x, currentPickup->getPosition().y - currentPickup->getSize().y);
				currentPickup->setSet(true);
			}

			if (currentPickup->getPosition().x >= view1.getCenter().x - (view1.getSize().x / 2) && currentPickup->getPosition().x
				+ currentPickup->getSize().x <= view1.getCenter().x + view1.getCenter().x + (view1.getSize().x / 2))
			{
				sf::FloatRect playerBox = player.getGlobalBounds();
				sf::FloatRect pickupBox = currentPickup->getGlobalBounds();

				if (playerBox.intersects(pickupBox))
				{
					currentPickup->collisions(playerBox);
					player.pickupResponse(currentPickup->getobjectType());
					currentPickup->setAlive(false);
				}
			}
			++currentPickup;
		}
	}

	for (int i = 0; i < enemy.size(); i++)
	{
		std::vector<Bullet> enemyBullets = enemy[i].getBullets();
		for (int j = 0; j < enemyBullets.size(); j++)
		{
			sf::FloatRect bulletBox = enemyBullets[i].getGlobalBounds();
			player.bulletCollision(bulletBox, enemyBullets[i].getammoType());
		}
	}


	

	if (position.x < 0)
		position.x = 0;

	if (position.x > 18000)
		position.x = 18000;

	view1.reset(sf::FloatRect(position.x, position.y, window->getSize().x, window->getSize().y));
}

// Render level
void Level::render()
{
	beginDraw();
	
	window->setView(view1);
	window->draw(Background);
	window->draw(player);
	player.renderArm(window);
	for (int i = 0; i < enemy.size(); i++)
	{
		window->draw(enemy[i]);
		enemy[i].renderArm(window);
	}

	for (int i = 0; i < platform.size(); i++)
	{
		window->draw(platform[i]);
	}

	for (int i = 0; i < pickups.size(); i++)
	{
		window->draw(pickups[i]);
	}

	window->setView(hudView);
	window->draw(hud);
	hud.renderCount(window);

	window->setView(view1);
	

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}


void Level::loadFoesandPlats()
{
	for (int i = 0; i < 67; i++)
	{
		if (platform[i].getPosition().y == 450)
		{
			plat.setPosition(platform[i].getPosition().x + 275, platform[i].getPosition().y - 175);
		}
		else if (platform[i].getPosition().y == 275)
		{
			int n = 0;
			n = rand() % 2 + 1;
			switch (n)
			{
			case 1:
				plat.setPosition(platform[i].getPosition().x + 275, platform[i].getPosition().y + 175);
				break;
			case 2:
				plat.setPosition(platform[i].getPosition().x + 275, platform[i].getPosition().y - 175);
				break;
			default:
				break;
			}
		}
		else if (platform[i].getPosition().y == 100)
		{
			plat.setPosition(platform[i].getPosition().x + 275, platform[i].getPosition().y + 175);
		}
		platform.push_back(plat);
	}

	for (int i = 0; i < platform.size(); i++)
	{
		int n = 0;
		n = rand() % 3 + 1;
		if (n < 3)
		{
			if (i > 3)
			{
				foe.setPosition(platform[i].getPosition().x, platform[i].getPosition().y - foe.getSize().y);
				foe.setAlive(true);
				enemy.push_back(foe);
			}
			else
			{
				Pickups loot;
				loot.setPosition(platform[i].getPosition().x + platform[i].getSize().x / 2, platform[i].getPosition().y);
				pickups.push_back(loot);
			}
		}
		else
		{
			Pickups loot;
			loot.setPosition(platform[i].getPosition().x + platform[i].getSize().x / 2, platform[i].getPosition().y);
			pickups.push_back(loot);
		}



	}
}
