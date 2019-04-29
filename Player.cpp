#include "Player.h"

Player::Player()
{
	initPlayer();
	setPosition(sf::Vector2f(0, 600 - getSize().y));
	velocity = sf::Vector2f(0, 0);
	health = 100;
	armour = 0;
	scale = 200.f;
	acceleration = 2.f;
	deceleration = 1.f;
	jump_force = 2.5f;
	max_speed = 175.f;
	gravity = 9.8f;
	moving = false;
	is_jumping = true;
	gunType = 1;
	setAmmo(1);
	pistol_ammo = 21;
	shotgun_ammo = 20;
	ar_ammo = 60;
	fireRate = sf::seconds(0.5);
}

Player::~Player() {}

//getters and setters
void Player::setClipSize(int i)
{
	switch (i)
	{
	case 1:
		clip_size = 7;
		break;
	case 2:
		clip_size = 4;
		break;
	case 3:
		clip_size = 30;
		break;
	}
}

void Player::setMaxAmmo(int i)
{
	switch (i)
	{
	case 1:
		max_ammo = 70;
		break;
	case 2:
		max_ammo = 80;
		break;
	case 3:
		max_ammo = 240;
		break;

	}
}

void Player::setAmmo(int i)
{
	switch (i)
	{
	case 1:
		current_ammo = current_pistol;
		setClipSize(i);
		setMaxAmmo(i);
		break;
	case 2:
		current_ammo = current_shotgun;
		setClipSize(i);
		setMaxAmmo(i);
		break;
	case 3:
		current_ammo = current_ar;
		setClipSize(i);
		setMaxAmmo(i);
		break;
	}
}

void Player::setJumping(bool b)
{
	is_jumping = b;
}

int Player::getHealth()
{
	return health;
}

int Player::getArmour()
{
	return armour;
}

int Player::getWeaponAmmo(int i)
{
	int n;
	n = 0;
	switch (i)
	{
	case 1:
		n = pistol_ammo;
		pistol_ammo -= pistol_ammo;
		return n;
		break;

	case 2:
		n = shotgun_ammo;
		shotgun_ammo -= shotgun_ammo;
		return n;
		break;

	case 3:
		n = ar_ammo;
		ar_ammo -= ar_ammo;
		return n;
		break;

	default:
		return n;
	}
}

int Player::getCurrentAmmo()
{
	return current_ammo;
}

int Player::getSpareAmmo()
{
	switch (gunType)
	{
	case 1:
		return pistol_ammo;
		break;
	case 2:
		return shotgun_ammo;
		break;
	case 3:
		return ar_ammo;
		break;
	default:
		break;
	}
}



//Player Functions

//handle player input
void Player::handleInput(float dt)
{
	Parm.setInput(input);
	//if player presses "W"
	if (input->isKeyDown(sf::Keyboard::W))
	{
		//if player isn't jumping
		if (!is_jumping)
		{
			//apply force upwards
			currentAnimation = &crouch;
			setSize(sf::Vector2f(42, 86));
			velocity.y -= (jump_force*scale);
			is_jumping = true;
		}
	}

	//if player presses "D"
	if (input->isKeyDown(sf::Keyboard::D))
	{

		//if player isnt jumping
		if (!is_jumping)
		{
			//move player and set him to the floor
			setPosition(getPosition().x, getPosition().y);
			moving = true;
			velocity.x += (acceleration * scale) *dt;
			maxSpeed(velocity.x);
			move(velocity*dt);
			currentAnimation = &walk;
			setSize(sf::Vector2f(42, 86));
			currentAnimation->animate(dt);
		}
		else
		{
			//move only in y axis if player is jumping.
			move(velocity*dt);
		}

	}

	//if player presses "A"
	else if (input->isKeyDown(sf::Keyboard::A))
	{
		//if player isnt jumping
		if (!is_jumping)
		{
			//move player and set him to the floor			
			setPosition(getPosition().x, getPosition().y);
			moving = true;
			velocity.x -= (acceleration * scale) *dt;
			maxSpeed(velocity.x);
			move(velocity*dt);
			currentAnimation = &walk;
			setSize(sf::Vector2f(42, 86));
			currentAnimation->animate(dt);
		}
		else
		{
			//move only in y axis if player is jumping.
			move(velocity*dt);
		}
	}

	//if player presses "S"
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		//if player isnt jumping
		if (!is_jumping)
		{
			//crouch character
			moving = false;
			currentAnimation = &crouch;
			setSize(sf::Vector2f(52, 66));
		}
	}
	else
	{
		//dont move character and make idle
		moving = false;
		move(velocity*dt);
		currentAnimation = &idle;
		setSize(sf::Vector2f(36, 88));
	}

	//if "R" is pressed reload
	if (input->isKeyDown(sf::Keyboard::R) && reloaded)
	{
		reloadClock.restart();
		reloaded = false;
		this->reload();
		input->setKeyUp(sf::Keyboard::R);
	}


	//switching players weapons
	if (input->isKeyDown(sf::Keyboard::Num1))
	{
		gunType = 1;

		setAmmo(1);
		current_ammo = current_pistol;
		fireRate = sf::seconds(0.5);
		Parm.changeWeapon(1);
	}

	if (input->isKeyDown(sf::Keyboard::Num2))
	{
		gunType = 2;
		setAmmo(2);
		current_ammo = current_shotgun;
		fireRate = sf::seconds(2);
		Parm.changeWeapon(2);
	}

	if (input->isKeyDown(sf::Keyboard::Num3))
	{
		gunType = 3;
		setAmmo(3);
		current_ammo = current_ar;
		fireRate = sf::seconds(0.2);
		Parm.changeWeapon(3);
	}

	//player shooting

	if (input->isMouseLDown() && reloaded && !fired && current_ammo != 0)
	{
		if (gunType == 1 || gunType == 2)
		{
			input->setMouseLDown(false);
			fireRateClock.restart();
			current_ammo--;
			fired = true;
			Parm.createBullet();
		}
		else
		{
			fireRateClock.restart();
			current_ammo--;
			fired = true;
			Parm.createBullet();

		}

	}

}

//Update player
void Player::update(float dt, sf::RenderWindow* window)
{
	velocity.y += (gravity*scale) * dt;
	move(velocity*dt);

	Parm.update(dt, getPosition(), window);
	firedTime = fireRateClock.getElapsedTime();
	reloadTime = reloadClock.getElapsedTime();


	wallBoundries(window, dt);
	setTextureRect(currentAnimation->getCurrentFrame());
	
	if (!moving)
	{
		slowDown(dt);
	}

	if (firedTime.asSeconds() >= fireRate.asSeconds())
	{
		fired = false;
	}

	if (reloadTime.asSeconds() >= reloadRate.asSeconds())
	{
		reloaded = true;
	}

	//if players arm is facing opposite way 
	if (Parm.getRotation() < 270 && Parm.getRotation() > 90)
	{
		//flip character
		currentAnimation->setFlipped(true);
	}
	else
	{
		//unflip character if arm is facing right way
		currentAnimation->setFlipped(false);
	}

}

//initalise player textures and animations
void Player::initPlayer()
{
	playerTexture.loadFromFile("gfx/Player_and_Arm.png");
	setTexture(&playerTexture);


	idle.addFrame(sf::IntRect(0, 19, 18, 44));

	walk.addFrame(sf::IntRect(26, 19, 21, 43));
	walk.addFrame(sf::IntRect(55, 19, 21, 43));
	walk.addFrame(sf::IntRect(86, 19, 25, 43));
	walk.setFrameSpeed(1.f / 10.f);

	crouch.addFrame(sf::IntRect(113, 30, 26, 33));

	currentAnimation = &idle;
	setSize(sf::Vector2f(36, 88));

}

//Reload Function
void Player::reload()
{
	if (current_ammo >= 1)
	{
		if (fullMag(gunType))
		{
			current_ammo = clip_size + 1;
		}
		else
		{
			current_ammo = getWeaponAmmo(gunType) + 1;
		}
	}
	else if (current_ammo == 0)
	{
		if (fullMag(gunType))
		{
			current_ammo = clip_size;
		}
		else
		{
			current_ammo = getWeaponAmmo(gunType);
		}
	}
	else if (current_ammo > clip_size)
	{
		//TODO Make noise signifying full mag
	}
}

//Slow player down when no keys are pressed
void Player::slowDown(float dt)
{
	if (velocity.x > 0)
	{
		velocity.x -= (deceleration * scale)  * dt;
	}
	else if (velocity.x < 0)
	{
		velocity.x += (deceleration * scale) *dt;
	}
	else
	{
		velocity.x = 0;
	}
}

//set players wall boundries so they can leave the bottom or left
void Player::wallBoundries(sf::RenderWindow* window, float dt)
{
	if (this->getPosition().x <= 0)
	{
		currentAnimation = &idle;
		setSize(sf::Vector2f(36, 88));
		velocity.x = 0;
		this->setPosition(0, this->getPosition().y);
	}
	else if (getPosition().x + getSize().x > 19200)
	{
		currentAnimation = &idle;
		velocity.x = 0;
		setPosition(19200 - getSize().x, getPosition().y);
	}

	if (this->getPosition().y >= window->getSize().y - this->getSize().y)
	{
		setPosition(this->getPosition().x, window->getSize().y - this->getSize().y);
		velocity.y = 0;
		is_jumping = false;
	}
	
	if (is_jumping)
	{
		std::cout << "not on plat \n";
		currentAnimation = &crouch;
		setSize(sf::Vector2f(52, 66));
		move(velocity*dt);
	}
}

//set player to max speed
void Player::maxSpeed(float speed)
{
	if (speed >= max_speed)
	{
		velocity.x = max_speed;
	}
	else if (speed <= -max_speed)
	{
		velocity.x = -max_speed;
	}
}

//check if players mag is full
bool Player::fullMag(int i)
{
	switch (i)
	{
	case  1:
		if (pistol_ammo > 7)
		{
			pistol_ammo -= 7;
			reloadRate = sf::seconds(2.2f);
			return true;
			break;
		}
		else
		{
			reloadRate = sf::seconds(1.2f);
			return false;
			break;
		}

	case 2:
		if (shotgun_ammo > 4)
		{
			reloadRate = sf::seconds(3.6f);
			shotgun_ammo -= 4;
			return true;
			break;
		}
		else
		{
			reloadRate = sf::seconds(2.8f);
			return false;
			break;
		}

	case 3:
		if (ar_ammo > 30)
		{
			reloadRate = sf::seconds(4.1f);
			ar_ammo -= 30;
			return true;
			break;
		}
		else
		{
			reloadRate = sf::seconds(2.6f);
			return false;
			break;
		}
	default:
		return false;
		break;
	}
}

void Player::renderArm(sf::RenderWindow * window)
{
	Parm.renderBullets(window);
	window->draw(Parm);
}

void Player::collisionResponse(sf::FloatRect platformBox, float dt)
{
	sf::FloatRect playerBox = getGlobalBounds();
	if (playerBox.left + playerBox.width > platformBox.left && playerBox.left < platformBox.left)
	{
		if (playerBox.top > platformBox.top && playerBox.top < platformBox.top + platformBox.height)
		{
			velocity.x = 0;
			setPosition(sf::Vector2f(platformBox.left - playerBox.width, playerBox.top));
		}
		
	}

	else if (playerBox.left < platformBox.width + platformBox.left && playerBox.left + playerBox.width > platformBox.width + platformBox.left)
	{
		if (playerBox.top > platformBox.top && playerBox.top < platformBox.top + platformBox.height)
		{
			velocity.x = 0;
			setPosition(sf::Vector2f(platformBox.left + platformBox.width, playerBox.top));
		}
	}
	
	if (playerBox.top + playerBox.height > platformBox.top && playerBox.top + playerBox.height < platformBox.top + platformBox.height)
	{
		if (playerBox.left + playerBox.width > platformBox.left && playerBox.left < platformBox.left + platformBox.width)
		{
			std::cout << "on platform \n";
			setPosition(getPosition().x, platformBox.top - getSize().y);
			velocity.y = 0;
			is_jumping = false;
		}
	}
	else if (playerBox.top < platformBox.top + platformBox.height && playerBox.top > platformBox.top)
	{
		if (playerBox.left + playerBox.width > platformBox.left && playerBox.left < platformBox.left + platformBox.width)
		{
			setPosition(playerBox.left, platformBox.top + platformBox.height);
			velocity.y = 0;
			is_jumping = true;
		}
	}
	
	
}

void Player::pickupResponse(int n)
{
	switch (n)
	{
	case 1:
		if (health <= 75)
		{
			health += 25;
		}
		else
		{
			health += (100 - health);
		}
		break;
	case 2:
		if (armour <= 75)
		{
			armour += 25;
		}
		else
		{
			armour += (100 - armour);
		}
		break;
	case 3:
		if (armour <= 50)
		{
			armour += 50;
		}
		else
		{
			armour += (100 - armour);
		}
		break;
	case 4:
		pistol_ammo += 14;
		break;
	case 5:
		shotgun_ammo += 8;
		break;
	case 6:
		ar_ammo += 30;
		break;
	}
}

void Player::bulletCollision(sf::FloatRect bulletBox, int bulletType)
{
	sf::FloatRect playerBox = getLocalBounds();

	if (bulletBox.intersects(playerBox))
	{
		switch (bulletType)
		{
		case 1:
			if (armour > 0)
			{
				armour -= 34;
			}
			else
			{
				health -= 34;
			}
			break;
		case 2:
			if (armour > 0)
			{
				armour -= 15;
			}
			else
			{
				health -= 15;
			}
			break;
		case 3:	if (armour > 0)
		{
			armour -= 66;
		}
				else
		{
			health -= 66;
		}
			break;
		}
	}
}
