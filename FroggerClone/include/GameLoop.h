#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

#include "Car.h"
#include "Log.h"
#include "Frog.h"
#include"FrogBase.h"


class GameLoop
{

public:

	GameLoop();
	~GameLoop();

	//This is the main function which runs the game from main.cpp
	void Run();

	//initialize logs and cars
	void initLogs();
	void initCars();

	//This function checks for collision between the frog and the other objects
	void CollisionLogic();

	//check win and loose condition
	void checkLose(sf::Event event);
	void checkWin(sf::Event event);


private:

	sf::RenderWindow* window;

	//creating the background,death screen, win screen and water objects
	sf::Texture BackgroundTexture, water, DeathScreenTexture, WinScreenTexture;
	sf::Sprite BackgroundSprite, DeathScreenSprite, WinScreenSprite;

	//car and log textures
	sf::Texture carTexture[5], logTexture[2];

	//the objects in the game
	std::vector<Car*> cars;
	std::vector<Log*> logs;
	Frog* frog;
	FrogBase* frogBase;

	//when the frog falls in in it dies
	sf::RectangleShape waterZone;

	// creating the death counter
	int deathCount;

	// this counts how many frog bases/flies the player has caught
	int SavedFrogHomes;
};


