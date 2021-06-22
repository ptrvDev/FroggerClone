#pragma once
#include <SFML/Graphics.hpp>

class Car
{
public:
	
	Car(const sf::Texture* texture, sf::Vector2f _pos, sf::Vector2f _size, float _speed);
	~Car();

	//draws the car textures, in order to be displayed(from the main.cpp)
	void draw(sf::RenderWindow& window);

	//This function holds the movement of the cars.
	void drive();

	//This function resets the car positions if the player chooses to retry the game after losing all 3 lifes.
	void reset();

	//get the collision shape
	sf::RectangleShape getCollisionShape();

private:
	//collision Shape
	sf::RectangleShape shape;

	//original spawning location
	sf::Vector2f  spawnPos;

	//speed of car
	float speed;
};

