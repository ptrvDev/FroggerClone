#include "FrogBase.h"

FrogBase::FrogBase()
{

	//loading the texture for the whole base, setting the size,scale and position
	theFrogBaseTexture.loadFromFile("assets/theFrogBase.png");
	theFrogBaseShape.setTexture(&theFrogBaseTexture);
	theFrogBaseShape.setSize(sf::Vector2f(216, 18));
	theFrogBaseShape.setPosition(4, 16);							    

	//loading the texture from the file, loading the texture into the shape, setting the size, scale and position.
	flyTexture.loadFromFile("assets/FrogHome.png");
	FlyBonusShape.setTexture(&flyTexture);
	FlyBonusShape.setSize(sf::Vector2f(16, 16));
	FlyBonusShape.setPosition(500, 16);


	SavedFrogHomeTexture.loadFromFile("assets/FrogHomeSaved.png");
	//For the first saved frog home 
	SavedFlyBonusShape[0].setTexture(&SavedFrogHomeTexture);
	SavedFlyBonusShape[0].setSize(sf::Vector2f(16, 16));
	SavedFlyBonusShape[0].setPosition(500, 500);

	//For the second saved frog home 
	SavedFlyBonusShape[1].setTexture(&SavedFrogHomeTexture);
	SavedFlyBonusShape[1].setSize(sf::Vector2f(16, 16));
	SavedFlyBonusShape[1].setPosition(500, 500);

	//For the third saved frog home 
	SavedFlyBonusShape[2].setTexture(&SavedFrogHomeTexture);
	SavedFlyBonusShape[2].setSize(sf::Vector2f(16, 16));
	SavedFlyBonusShape[2].setPosition(500, 500);

	//For the fourth saved frog home 
	SavedFlyBonusShape[3].setTexture(&SavedFrogHomeTexture);
	SavedFlyBonusShape[3].setSize(sf::Vector2f(16, 16));
	SavedFlyBonusShape[3].setPosition(500, 500);

	//For the fifth saved frog home 
	SavedFlyBonusShape[4].setTexture(&SavedFrogHomeTexture);
	SavedFlyBonusShape[4].setSize(sf::Vector2f(16, 16));
	SavedFlyBonusShape[4].setPosition(500, 500);

	//boolean  indicating wether or not a frog base has been reached
	FrogBaseReached[0] = false;
	FrogBaseReached[1] = false;
	FrogBaseReached[2] = false;
	FrogBaseReached[3] = false;
	FrogBaseReached[4] = false;

	//how many frog bases have been reached
	//(this is used later in an if statement. If more than 3 bases have been  reached, the next 2 bases will spawn faster
	spawnPointsTakenCount = 0;
}


FrogBase::~FrogBase()
{
}

void FrogBase::spawnFly() {
	if (flyTimer.getElapsedTime().asSeconds() > 7.5f)
	{
		//next 5 lines of code are used for generating a random number between 1 and 5. The position of the FrogHome depends on the number the algorithm chooses


		if (spawnPointsTakenCount > 3)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(4, 8);
			flyPosValue = dis(gen);
			flyPos = flyPosValue;
		}
		else if (spawnPointsTakenCount <= 3)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(1, 8);
			flyPosValue = dis(gen);
			flyPos = flyPosValue;
		}

		flyTimer.restart();

		//This sets the frog base/home position of the screen. I've added 3 of these, because I dont want the base always spawning on the screen.
				//This sets the frog base/home position of the screen. I've added 3 of these, because I dont want the base always spawning on the screen.
		if (flyPos == 1)
		{
			FlyBonusShape.setPosition(500 , 500 );
		}
		if (flyPos == 2)
		{
			FlyBonusShape.setPosition(500 , 16 );
		}
		if (flyPos == 3)
		{
			FlyBonusShape.setPosition(500, 500);
		}
		else if (flyPos == 4)
		{
			if (FrogBaseReached[0] == false)
			{
				FlyBonusShape.setPosition(8 , 16 );
			}
			else if (FrogBaseReached[0] == true)
			{
				FlyBonusShape.setPosition(500, 500);
			}
		}
		else if (flyPos == 5)
		{
			if (FrogBaseReached[1] == false)
			{
				FlyBonusShape.setPosition(56 , 16 );
			}
			else if (FrogBaseReached[1] == true)
			{
				FlyBonusShape.setPosition(500, 500);
			}
		}
		else if (flyPos == 6)
		{
			if (FrogBaseReached[2] == false)
			{
				FlyBonusShape.setPosition(104 , 16 );
			}
			else if (FrogBaseReached[2] == true)
			{
				FlyBonusShape.setPosition(500, 500);
			}
		}
		else if (flyPos == 7)
		{
			if (FrogBaseReached[3] == false)
			{
				FlyBonusShape.setPosition(152 , 16 );
			}
			else if (FrogBaseReached[3] == true)
			{
				FlyBonusShape.setPosition(500, 500);
			}
		}
		else if (flyPos == 8)
		{
			if (FrogBaseReached[4] == false)
			{
				FlyBonusShape.setPosition(200 , 16 );
			}
			else if (FrogBaseReached[4] == true)
			{
				FlyBonusShape.setPosition(500, 500);
			}
		}
	}



}


void FrogBase::draw(sf::RenderWindow& window) {
	//draws the shapes, which are displayed after that(from the main.cpp)
	window.draw(theFrogBaseShape);

	window.draw(FlyBonusShape);
	for (int i = 0; i < 5; i++) {
		window.draw(SavedFlyBonusShape[i]);
	}

}


sf::RectangleShape FrogBase::returnFlyShape() {
	//Returns the frog shape, which is used in the main.cpp for detecting collision between the frog and the different cars
	return FlyBonusShape;
}


sf::RectangleShape FrogBase::returnTheFrogBaseShape() {
	//Returns the frog shape, which is used in the main.cpp for detecting collision between the frog and the different cars
	return theFrogBaseShape;
}


sf::RectangleShape FrogBase::returnSavedBaseShape(int i) {
	return SavedFlyBonusShape[i];
}


void FrogBase::gotFlyBonus() {

	//if the frog reaches a home base/fly, the saved home/base texture appears at its position
	SavedFrogHomePosX = FlyBonusShape.getGlobalBounds().left;
	SavedFrogHomePosY = FlyBonusShape.getGlobalBounds().top;

	std::cout << "Frog has successfully collided with a fly\n";
	std::cout << "Player caught fly at position X - " << SavedFrogHomePosX << " and position Y - " << SavedFrogHomePosY << "\n\n";

	if (SavedFrogHomePosX == 200)
	{
		SavedFlyBonusShape[4].setPosition(SavedFrogHomePosX, SavedFrogHomePosY);
		FrogBaseReached[4] = true;
		spawnPointsTakenCount++;

	}
	else if (SavedFrogHomePosX == 152)
	{
		SavedFlyBonusShape[3].setPosition(SavedFrogHomePosX, SavedFrogHomePosY);
		FrogBaseReached[3] = true;
		spawnPointsTakenCount++;
	}
	else if (SavedFrogHomePosX == 104)
	{
		SavedFlyBonusShape[2].setPosition(SavedFrogHomePosX, SavedFrogHomePosY);
		FrogBaseReached[2] = true;
		spawnPointsTakenCount++;
	}
	else if (SavedFrogHomePosX == 56)
	{
		SavedFlyBonusShape[1].setPosition(SavedFrogHomePosX, SavedFrogHomePosY);
		FrogBaseReached[1] = true;
		spawnPointsTakenCount++;
	}
	else if (SavedFrogHomePosX = 8)
	{
		SavedFlyBonusShape[0].setPosition(SavedFrogHomePosX, SavedFrogHomePosY);
		FrogBaseReached[0] = true;
		spawnPointsTakenCount++;
	}
	std::cout << "Score is successfully update\n";
	std::cout << " +900 score\n\n";

	std::cout << spawnPointsTakenCount << " flies/home bases are caught by the frog \n\n";

}


void FrogBase::FrogHomeReset() {

	//the function resets everything, if the player wants to retry/play a new game

	for (int i = 0; i < 5; i++)
	{
		SavedFlyBonusShape[i].setPosition(500, 16);
	}

	FrogBaseReached[0] = false;
	FrogBaseReached[1] = false;
	FrogBaseReached[2] = false;
	FrogBaseReached[3] = false;
	FrogBaseReached[4] = false;

	spawnPointsTakenCount = 0;

}


//if a certain frog base is reached, the saved home texture appears at it's location
void FrogBase::FrogHomeReached(int i) {
	switch (i)
	{
	case 0:
		SavedFlyBonusShape[0].setPosition(8 , 16 );
		FrogBaseReached[0] = true;
		spawnPointsTakenCount++;
		break;

	case 1:
		SavedFlyBonusShape[1].setPosition(56 , 16 );
		FrogBaseReached[1] = true;
		spawnPointsTakenCount++;
		break;

	case 2:
		SavedFlyBonusShape[2].setPosition(104 , 16 );
		FrogBaseReached[2] = true;
		spawnPointsTakenCount++;
		break;

	case 3:
		SavedFlyBonusShape[3].setPosition(152 , 16 );
		FrogBaseReached[3] = true;
		spawnPointsTakenCount++;
		break;

	case 4:
		SavedFlyBonusShape[4].setPosition(200 , 16 );
		FrogBaseReached[4] = true;
		spawnPointsTakenCount++;
		break;
	}
}

