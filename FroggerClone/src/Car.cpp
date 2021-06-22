#include "Car.h"

Car::Car(const sf::Texture* texture, sf::Vector2f _pos, sf::Vector2f _size, float _speed)
{
	shape.setTexture(texture);
	shape.setPosition(_pos.x, _pos.y);
	shape.setSize(_size);
	speed = _speed;
	spawnPos = _pos;
}

Car::~Car()
{
}

void Car::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Car::drive()
{
	shape.move(speed/3, 0);

	if (speed > 0 && shape.getPosition().x > 240)
	{
		shape.setPosition(-16, spawnPos.y);
	}

	if (speed < 0 && shape.getPosition().x < -16)
	{
		shape.setPosition(224, spawnPos.y);
	}
}

void Car::reset()
{
	shape.setPosition(spawnPos);
}

sf::RectangleShape Car::getCollisionShape()
{
	return shape;
}
