#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <Frog.h>


class FrogBase
{
public:
public:
	//Initializes the frog homes at the (the ones that spawn at the end of the level)
	FrogBase();
	~FrogBase();

	//draws the frog home (including the saved frog home) in order to be displayed from main.cpp
	void draw(sf::RenderWindow& window);


	// the function that spawns them
	void spawnFly();

	//function when the frog reaches the fly
	void gotFlyBonus();

	//return the fly shape
	sf::RectangleShape returnFlyShape();

	//the function resets everything, if the player wants to retry/play a new game
	void FrogHomeReset();

	//return the frog base shape
	sf::RectangleShape returnTheFrogBaseShape();

	//return the shape of the already saved bases/caught flies
	sf::RectangleShape returnSavedBaseShape(int i);

	//reached frog homes
	void FrogHomeReached(int i);


private:
	//creating the shape of the frog base
	sf::RectangleShape theFrogBaseShape;

	//creating the texture for the shape of the frog base
	sf::Texture theFrogBaseTexture;

	//creating the shape for the fly  at the end of the map
	sf::RectangleShape FlyBonusShape;

	//creating the shape for the fly at the end of the map
	sf::RectangleShape SavedFlyBonusShape[5];

	//creating the texture for fly at the end of the map
	sf::Texture flyTexture;

	//creating the texture for the Saved frog home
	sf::Texture SavedFrogHomeTexture;

	//This is a timer which after it passes certain amount of time, the frog home respawns at a different location
	sf::Clock flyTimer;

	//Indicator for the  fly at the end of the map spawn positioning
	int flyPos;

	//The value of the indicator
	int flyPosValue;

	//if the player gets a fly or reaches a home base, these two integers save the location of the frog home in order to initialize the Frog Home Saved shape
	int SavedFrogHomePosX;
	int SavedFrogHomePosY;


	//returns true if the particular frog base has been reached, and false if it still hasnt
	bool FrogBaseReached[5];

	//Counter for how many spawn points are taken. if there are 4 spawn points taken, the 5th one is going to spawn sooner than usual (because I figured out you have to wait a lot otherwise)
	int spawnPointsTakenCount;



};

