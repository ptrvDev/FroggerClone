#include "Log.h"

Log::Log(const sf::Texture* texture, sf::Vector2f _pos, sf::Vector2f _size, float _speed)
{
	shape.setTexture(texture);
	shape.setPosition(_pos);
	shape.setSize(_size);
	speed = _speed;
	spawnPos = _pos;
}

Log::~Log()
{
}

void Log::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Log::FloatOnWater()
{
	shape.move(speed/3, 0);

	if (speed > 0 && shape.getPosition().x > 307)
	{
		shape.setPosition(-63, spawnPos.y);
	}

	if (speed < 0 && shape.getPosition().x < -42)
	{
		shape.setPosition(244, spawnPos.y);
	}
}

void Log::reset()
{
	shape.setPosition(spawnPos);
}

sf::RectangleShape Log::getCollisionShape()
{
	return shape;
}

float Log::GetSpeed()
{
	return speed;
}
