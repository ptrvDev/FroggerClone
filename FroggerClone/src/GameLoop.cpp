#pragma once
#include "GameLoop.h"
#include <iostream>


GameLoop::GameLoop()
{
	//224,240
	window = new sf::RenderWindow(sf::VideoMode(224, 240), "Frogger");

	//make the screen 3 times bigger
	window->setSize(sf::Vector2u(224*3, 240*3));

	//setting the frame limit(since on computers with faster processors, everything would move faster)
	window->setFramerateLimit(60);

	//create the player, cars and logs
	initCars();
	initLogs();
	frog = new Frog();
	frogBase = new FrogBase();

	//Setting the background
	BackgroundTexture.loadFromFile("Assets/Background.png");
	BackgroundSprite.setTexture(BackgroundTexture);
	BackgroundSprite.setPosition(0, 0);
	water.loadFromFile("Assets/water.png");
	waterZone.setTexture(&water);
	waterZone.setSize(sf::Vector2f(224, 80));
	waterZone.setPosition(0, 16);

	//adjusting the deathCount to 0 when a new game is started
	deathCount = 0;

	//adjusting the deathCount to 0 when a new game is started
	SavedFrogHomes = 0;
}


GameLoop::~GameLoop()
{
	for (auto car : cars)
	{
		delete car;
		car = NULL;
	}	
	cars.clear();

	for (auto log : logs)
	{
		delete log;
		log = NULL;
	}
	logs.clear();

	delete frog;
	frog = NULL;

	delete frogBase;
	frog = NULL;

	delete window;
	window = NULL;
}


void GameLoop::Run()
{
	while (window->isOpen())
	{
		sf::Event event;

		while (window->pollEvent(event))
		{

			switch (event.type)
			{

			case sf::Event::Closed:
				window->close();
				break;

			case sf::Event::Resized:
				//window->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
				break;

			case sf::Event::KeyPressed:
				//movement of the frog
				frog->move(event);
				break;

			case sf::Event::KeyReleased:
				//when escape is pressed, the game closes.
				if (event.key.code == sf::Keyboard::Escape)
				{
					window->close();
				}

				break;

			default:
				break;

			}
		}

		//see if frog collides with anything
		CollisionLogic();

		//spawn fly 
		frogBase->spawnFly();

		//check if player won the game
		checkWin(event);

		//check if player lost the game
		checkLose(event);

		if (deathCount != 3 && SavedFrogHomes != 5)
		{		


			//clears the window
			window->clear();

			////drawing the background 
			window->draw(BackgroundSprite);
			window->draw(waterZone);

			//draws cars
			for (auto car : cars)
			{
				car->drive();
				car->draw(*window);
			}

			//draw logs
			for (auto log : logs)
			{
				log->FloatOnWater();
				log->draw(*window);
			}

			//draws the frog object
			frog->draw(*window);
			frogBase->draw(*window);

			//display all drawn objects
			window->display();
		}
	}
}


void GameLoop::initCars()
{
	carTexture[0].loadFromFile("Assets/Car1.png"); //this texture is for the cars driving on the 1st lane
	carTexture[1].loadFromFile("Assets/Car2.png"); //this texture is for the cars driving on the 2st lane
	carTexture[2].loadFromFile("Assets/Car3.png"); //this texture is for the cars driving on the 3st lane
	carTexture[3].loadFromFile("Assets/Car4.png"); //this texture is for the cars driving on the 3st lane
	carTexture[4].loadFromFile("Assets/Car5.png"); //this texture is for the cars driving on the 3st lane
	
	Car* car = new Car(&carTexture[0], sf::Vector2f(130, 176), sf::Vector2f(16, 16), -1.5);
	cars.push_back(car);

	car = new Car(&carTexture[0], sf::Vector2f(224, 176), sf::Vector2f(16, 16), -1.5);
	cars.push_back(car);

	car = new Car(&carTexture[0], sf::Vector2f(318, 176), sf::Vector2f(16, 16), -1.5);
	cars.push_back(car);

	car = new Car(&carTexture[0], sf::Vector2f(25, 160), sf::Vector2f(16, 16), 1);
	cars.push_back(car);

	car = new Car(&carTexture[1], sf::Vector2f(-50, 160), sf::Vector2f(16, 16), 1);
	cars.push_back(car);

	car = new Car(&carTexture[1], sf::Vector2f(-175, 160), sf::Vector2f(16, 16), 1);
	cars.push_back(car);

	car = new Car(&carTexture[2], sf::Vector2f(183, 144), sf::Vector2f(16, 16), -2);
	cars.push_back(car);

	car = new Car(&carTexture[2], sf::Vector2f(100, 144), sf::Vector2f(16, 16), -2);
	cars.push_back(car);

	car = new Car(&carTexture[2], sf::Vector2f(275, 144), sf::Vector2f(16, 16), -2);
	cars.push_back(car);

	car = new Car(&carTexture[3], sf::Vector2f(55, 128), sf::Vector2f(16, 16), 1.5);
	cars.push_back(car);

	car = new Car(&carTexture[3], sf::Vector2f(-25, 128), sf::Vector2f(16, 16), 1.5);
	cars.push_back(car);

	car = new Car(&carTexture[3], sf::Vector2f(-100, 128), sf::Vector2f(16, 16), 1.5);
	cars.push_back(car);

	car = new Car(&carTexture[4], sf::Vector2f(250, 112), sf::Vector2f(32, 16), -1);
	cars.push_back(car);

	car = new Car(&carTexture[4], sf::Vector2f(350, 112), sf::Vector2f(32, 16), -1);
	cars.push_back(car);

	car = new Car(&carTexture[4], sf::Vector2f(-450, 112), sf::Vector2f(32, 16), -1);
	cars.push_back(car);

}


void GameLoop::initLogs()
{
	logTexture[0].loadFromFile("Assets/log.png");
	logTexture[1].loadFromFile("Assets/bigLog.png");


	//FIRST LANE LOGS
	Log* log = new Log(&logTexture[0], sf::Vector2f(160, 82), sf::Vector2f(42,12), -1.5);
    logs.push_back(log);

	log = new Log(&logTexture[0], sf::Vector2f(244, 82), sf::Vector2f(42, 12), -1.5);
	logs.push_back(log);

	log = new Log(&logTexture[0], sf::Vector2f(328, 82), sf::Vector2f(42, 12), -1.5);
	logs.push_back(log);


	//THE BIG LOGS FOR THE SECOND LANE
	log = new Log(&logTexture[1], sf::Vector2f(126, 66), sf::Vector2f(63, 12), 1.5);
	logs.push_back(log);

	log = new Log(&logTexture[1], sf::Vector2f(-126, 66), sf::Vector2f(63, 12), 1.5);
	logs.push_back(log);


	//THE LOGS FOR THE THIRD LANE
	log = new Log(&logTexture[0], sf::Vector2f(118, 50), sf::Vector2f(42, 12), -1.5);
	logs.push_back(log);

	log = new Log(&logTexture[0], sf::Vector2f(202, 50), sf::Vector2f(42, 12), -1.5);
	logs.push_back(log);

	log = new Log(&logTexture[0], sf::Vector2f(286, 50), sf::Vector2f(42, 12), -1.5);
	logs.push_back(log);


	//THE LOGS FOR THE FOURTH LANE
	log = new Log(&logTexture[1], sf::Vector2f(63, 34), sf::Vector2f(63, 12), 1.5);
	logs.push_back(log);

	log = new Log(&logTexture[1], sf::Vector2f(168, 34), sf::Vector2f(63, 12), 1.5);
	logs.push_back(log);

}


void GameLoop::CollisionLogic()
{
	//check for car collision
	for (auto car : cars)
	{
		if (frog->returnShape().getGlobalBounds().intersects(car->getCollisionShape().getGlobalBounds()))
		{
			//This triggers the frog.death() function in Frog.cpp
			frog->death();

			//adds 1 to the death counter. The death counter is used at line 99 and 121.
			deathCount += 1;

			std::cout << "Frog has collided with vehicle successfully\n";
			std::cout << "Player has been hit by a vehicle\n";
			return;
		}
	}


	//check for log collision
	if (frog->returnShape().getGlobalBounds().intersects(waterZone.getGlobalBounds()))
	{
		bool inWater = true;
		bool gotFly = false;
		
		for (auto log : logs)
		{
			if (frog->returnShape().getGlobalBounds().intersects(log->getCollisionShape().getGlobalBounds()))
			{
				inWater = false;

				//carries the frog left or right depending on the direction of the wooden logs
				if (log->GetSpeed() > 0)
				{
					frog->getCarriedRight();
				}
				else if (log->GetSpeed() <= 0)
				{
					frog->getCarriedLeft();
				}
			}
		}

		//if the frog gets a fly, the player doesn't die from the water
		if (frog->returnShape().getGlobalBounds().intersects(frogBase->returnFlyShape().getGlobalBounds()))
		{
			inWater = false;
			gotFly = true;

		}

		//if the frog reaches a frog base, the player doesn't die from the water
		if (gotFly == false)
		{

			if ((frog->returnShape().getPosition().x > 6) && (frog->returnShape().getPosition().x < 33) && (frog->returnShape().getPosition().y < 30))
			{
				std::cout << "frog got home base at X position: " << frog->returnShape().getPosition().x;
				inWater = false;
				//tells the frog.cpp that end of the level has been reached, and then the frog respawns at the beginning
				frog->endOfLevelReached();

				//tells the frogHome.cpp that a frog home has be reached, and a saved frog base appears on the screen
				frogBase->FrogHomeReached(0);

				//adds 1 to the saved frog homes(and when it reaches 5, the player wins the game)
				SavedFrogHomes += 1;
			}

			//handles collision if the frog catches a fly
			if ((frog->returnShape().getPosition().x > 50) && (frog->returnShape().getPosition().x < 80) && (frog->returnShape().getPosition().y < 30))
			{
				std::cout << "frog got home base at X position: " << frog->returnShape().getPosition().x;
				inWater = false;
				frog->endOfLevelReached();
				frogBase->FrogHomeReached(1);
				SavedFrogHomes += 1;
			}
			if ((frog->returnShape().getPosition().x > 98) && (frog->returnShape().getPosition().x < 128) && (frog->returnShape().getPosition().y < 30))
			{
				std::cout << "frog got home base at X position: " << frog->returnShape().getPosition().x;
				inWater = false;
				frog->endOfLevelReached();
				frogBase->FrogHomeReached(2);
				SavedFrogHomes += 1;
			}
			if ((frog->returnShape().getPosition().x > 148) && (frog->returnShape().getPosition().x < 178) && (frog->returnShape().getPosition().y < 30))
			{
				std::cout << "frog got home base at X position: " << frog->returnShape().getPosition().x;
				inWater = false;
				frog->endOfLevelReached();
				frogBase->FrogHomeReached(3);
				SavedFrogHomes += 1;
			}
			if ((frog->returnShape().getPosition().x > 196) && (frog->returnShape().getPosition().x < 226) && (frog->returnShape().getPosition().y < 30))
			{
				std::cout << "frog got home base at X position: " << frog->returnShape().getPosition().x;
				inWater = false;
				frog->endOfLevelReached();
				frogBase->FrogHomeReached(4);
				SavedFrogHomes += 1;
			}


			//if the frog is not at a home base or a log - loses a life
			if (inWater == true)
			{
				frog->death();
				deathCount += 1;
				std::cout << "Frog has collided with River successfully\n";
				std::cout << "Player has fallen in the river\n";
			}
		}


		//This kills the player if he goes off the screen
		if (((frog->returnShape().getPosition().x > 210) && (frog->returnShape().getPosition().y > 96)) || ((frog->returnShape().getPosition().x < 16 && (frog->returnShape().getPosition().y > 96))) || ((frog->returnShape().getPosition().x > 224) && (frog->returnShape().getPosition().y < 96)) || ((frog->returnShape().getPosition().x < 0 && (frog->returnShape().getPosition().y < 96))) || (frog->returnShape().getPosition().y > 208))
		{
			frog->death();
			deathCount++;

			std::cout << "Frog is successfully detected being out of the window borders\n";
			std::cout << "Player has died\n";
		}

		//If the frog reaches a fly and gets a Frog Home
		if (frog->returnShape().getGlobalBounds().intersects(frogBase->returnFlyShape().getGlobalBounds()))
		{
			frog->gotFlyBonus(); // This line gives the frog 1000 points score and respawns the player
			frogBase->gotFlyBonus(); // This line draws the Frog Home saved object 
			SavedFrogHomes += 1; //This line of code adds 1 to the SavedFrogHomes
			if (deathCount != 0)
			{
				deathCount -= 1; //because the frog earns 1 bonus live(from the Frog.cpp's gotFlyBonus function), 1 is being substracted from the deathcounter 
			}
		}
	}
}


void GameLoop::checkLose(sf::Event event)
{
	DeathScreenTexture.loadFromFile("Assets/DeathScreen.png");
	DeathScreenSprite.setTexture(DeathScreenTexture);


	if (deathCount == 3) {
		window->clear();
		window->draw(DeathScreenSprite);
		window->display();


		if (sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::N)
			{
				window->close();
			}

			if (event.key.code == sf::Keyboard::Y)
			{
				//if the user decides to press Y, everything resets to default and a new game is launched
				deathCount = 0;
				SavedFrogHomes = 0;
				frog->reset();
				for (auto car : cars)
				{
					car->reset();
				}
				frogBase->FrogHomeReset();
				system("CLS");
				std::cout << "Game successfully restarted\n";
				std::cout << "Player has chosen to retry\n\n";
			}
			else if ((event.key.code != sf::Keyboard::N) && (event.key.code != sf::Keyboard::Y)) {
				//Do nothing
			}
		}
	}
}


void GameLoop::checkWin(sf::Event event)
{
	WinScreenTexture.loadFromFile("Assets/WinScreen.png");
	WinScreenSprite.setTexture(WinScreenTexture);


	if (SavedFrogHomes == 5) {
		window->clear();
		window->draw(WinScreenSprite);
		window->display();
		if (sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::N)
			{
				window->close();
			}

			else if (event.key.code == sf::Keyboard::Y)
			{
				//if the user decides to press Y, everything resets to default and a new game is launched
				SavedFrogHomes = 0;
				deathCount = 0;
				frog->reset();
				for (auto car : cars)
				{
					car->reset();
				}
				frogBase->FrogHomeReset();
				system("CLS");
				std::cout << "Game successfully restarted\n";
				std::cout << "Player chose to play again\n\n";
			}
			else if ((event.key.code != sf::Keyboard::N) && (event.key.code != sf::Keyboard::Y)) {
				//Do nothing
			}
		}
	}
}


