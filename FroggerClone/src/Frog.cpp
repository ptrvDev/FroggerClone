#include "Frog.h"
#include <iostream>


Frog::Frog()
{
	//Loading the frog texture
	frogTexture.loadFromFile("Assets/Frog.png");

	//Loading the frog lifes texture
	froglifesTexture.loadFromFile("Assets/Froglifes.png");

	//Loading the death screen texture 
	deathScreenTexture.loadFromFile("Assets/DeathScreen.png");

	//Loading the Score texture
	ScoreTexture.loadFromFile("Assets/ScoreSheet.png");

	//loading the sound files and adjusting them
	playerDiesSoundBuff.loadFromFile("Assets/219992__b-lamerichs__45.wav");
	playerDiesSound.setBuffer(playerDiesSoundBuff);
	playerReachesHomeSoundBuff.loadFromFile("Assets/219959__b-lamerichs__16.wav");
	playerReachesHomeSound.setBuffer(playerReachesHomeSoundBuff);

	//Setting the texture we loaded in the sprite object
	frogShape.setTexture(&frogTexture);

	// Loading the death screen texture into the death screen sprite
	deathScreenSprite.setTexture(deathScreenTexture);

	//Loading the score texture into the score sprite
	ScoreSprite.setTexture(ScoreTexture);

	//Loading the frog texture into the frog sprite
	froglifesSprite.setTexture(froglifesTexture);

	//Adjusting the frog lifes texture rectangle
	froglifesRect.height = 6;
	froglifesRect.width = 41;

	//Adjusting the score texture rectangle
	ScoreRect.height = 7;
	ScoreRect.width = 32;

	//loading the frog lifes texture rectangle into the frog sprite
	froglifesSprite.setTextureRect(froglifesRect);

	//loading the score texture rectange into the score sprite
	ScoreSprite.setTextureRect(ScoreRect);


	//Setting the origin of the frog sprite (used for rotating the object around its centre)
	frogShape.setOrigin(6.5, 5);

	//Setting the position of the frog sprite when the game starts
	frogShape.setPosition(sf::Vector2f(112, 200));

	//Setting the position of the frog lifes
	froglifesSprite.setPosition(63, 3 );


	//Setting he position of the score board
	ScoreSprite.setPosition(176 , 2);

	//Setting the original size of the frog shape (16 by 16 pixels, the same as the texture)
	frogShape.setSize(sf::Vector2f(13, 10));

	//Scaling the frog sprite according to the screen size
	//frogShape.setScale(scale, scale);
	//
	//
	////Setting the scale of the score board according to the screen size
	//ScoreSprite.setScale(scale, scale);
	//
	////Scaling the frog lifes sprite according to the screen size
	//froglifesSprite.setScale(scale, scale);

	//lifes of the frog
	lives = 3;

}



Frog::~Frog()
{

}


void Frog::draw(sf::RenderWindow& window)
{

	//displays the frog 
	window.draw(frogShape);

	//displays the frog lifes 
	window.draw(froglifesSprite);

	window.draw(ScoreSprite);


}

//Returns the frog shape, which is used in the main.cpp for detecting collision between the frog and the different cars
sf::RectangleShape Frog::returnShape()
{
	return frogShape;
}


void Frog::move(sf::Event event) {

	//The movement of the frog (Left, Right, Up, Down)
	if (sf::Keyboard::Key::Left == event.key.code)
	{

		//Clock for the movement(making it seem like the frog is moving on tiles)
		if (movementClock.getElapsedTime().asSeconds() > 0.2f)
		{

			//Moving the sprite
			frogShape.move(-16, 0);

			//Rotating the sprite
			frogShape.setRotation(270.f);

			movementClock.restart();



		}
	}

	else if (sf::Keyboard::Key::Right == event.key.code)
	{
		if (movementClock.getElapsedTime().asSeconds() > 0.1f)
		{
			frogShape.move(16, 0);
			frogShape.setRotation(90.f);
			movementClock.restart();
			std::cout << "Player input successfully detected\n";
			std::cout << "Frog has moved right\n\n";
		}
	}

	else if (sf::Keyboard::Key::Up == event.key.code)
	{
		if (movementClock.getElapsedTime().asSeconds() > 0.1f)
		{

			frogShape.move(0, -16);
			frogShape.setRotation(0.f);
			movementClock.restart();
			std::cout << "Player input successfully detected\n";
			std::cout << "Frog has moved up\n\n";

			//updating score

			if ((ScoreRect.left == 0) || (ScoreRect.left < 320))
			{
				ScoreRect.left += 32;
				ScoreSprite.setTextureRect(ScoreRect);
				std::cout << "Score is successfully update\n";
				std::cout << " +10 score\n\n";
			}

		}
	}

	else if (sf::Keyboard::Key::Down == event.key.code)
	{
		if (movementClock.getElapsedTime().asSeconds() > 0.1f)
		{

			frogShape.move(0, 16);
			frogShape.setRotation(180.f);
			std::cout << "Player input successfully detected\n";
			std::cout << "Frog has moved down\n\n";

			movementClock.restart();
			if (ScoreRect.left > 32)
			{
				ScoreRect.left -= 32;
				ScoreSprite.setTextureRect(ScoreRect);
				std::cout << "Score is successfully update\n";
				std::cout << " -10 score\n\n";
			}
		}
	}
}


void Frog::getCarriedLeft()
{
	frogShape.move(-0.5, 0);
}


void Frog::getCarriedRight()
{
	frogShape.move(0.5, 0);
}


void Frog::death()
{
	//This function is triggered by the collision detection from the main.cpp

	//if the player has more than 0 lifes and collides with a car, 1 life is taken from the frog life system (which is displayed at the top left corner of the screen)
	// and also the frog is respawned at the bottom of the screen
	if (0 < lives)
	{
		frogShape.setPosition(sf::Vector2f(112, 200));
		lives -= 1;
		froglifesRect.width -= 12;
		froglifesSprite.setTextureRect(froglifesRect);

		//resets the player score
		ScoreRect.left = 0;
		ScoreSprite.setTextureRect(ScoreRect);
	}
	if (0 >= lives)
	{
		//if the frog has zero lifes nothing happens to the frog, but the main function is playing it's role here.
		//if the frog dies 3 times, a "Retry? Y or No" screen is triggered from the main function.
	}
	playerDiesSound.play();

}


void Frog::reset() {

	//resets the player lifes
	lives = 3;
	froglifesRect.height = 6;
	froglifesRect.width = 41;
	froglifesSprite.setTextureRect(froglifesRect);

	//resets the player score
	ScoreRect.left = 0;
	ScoreRect.top = 0;
	ScoreSprite.setTextureRect(ScoreRect);

	//resets the player position 
	frogShape.setPosition(sf::Vector2f(112, 200));
}


void Frog::endOfLevelReached() {
	frogShape.setPosition(sf::Vector2f(112, 200));
	playerReachesHomeSound.play();
}


void Frog::gotFlyBonus() {
	//when the frog gets a fly(at the end of the level) gets respawned at the beginning of the level and earns 1000 score points
	frogShape.setPosition(sf::Vector2f(112, 200));
	ScoreRect.left = 0;
	ScoreRect.top += 7;
	ScoreSprite.setTextureRect(ScoreRect);
	playerReachesHomeSound.play();

	if ((lives > 0) && (lives < 3))
	{
		lives += 1;
		froglifesRect.width += 12;
		froglifesSprite.setTextureRect(froglifesRect);
		std::cout << "Player earns 1 bonus live\n";
	}

	else if (lives == 3)
	{
		lives = 3;
		std::cout << "Player has maximum lives!\n";
	}
}


