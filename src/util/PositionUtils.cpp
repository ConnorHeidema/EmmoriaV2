#include "util/PositionUtils.hpp"
#include "util/OverlapUtils.hpp"

#include "util/Position.hpp"
#include "util/Size.hpp"
#include <math.h>

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <util/Graphics/RectangularBoundaryCollision.hpp>

Position PositionUtils::CalculatePositionFromSpeed(Position const& fromOldPosition, double const& speed, double const& angle)
{
	return Position
	{
		fromOldPosition.x + speed * cos(angle),
		fromOldPosition.y + speed * sin(angle)
	};
}

void PositionUtils::CalculateNewPosition(Position& position, double const& speed, double const& angle)
{
	position.x += speed * cos(angle);
	position.y += speed * sin(angle);
}

void PositionUtils::PrintPosition(Position const& position, std::string const& prefix)
{
	if (prefix == "")
	{
		std::cout << "(" << position.x << ", " << position.y << ")" << std::endl;
	}
	else
	{
		std::cout << prefix << ": (" << position.x << ", " << position.y << ")" << std::endl;
	}
}

void PositionUtils::SetObjectToViablePosition(
		Position& positionToRevert,
		Position const& lastPosition,
		Size const& objectSize,
		Position const& wallPosition,
		Size const& wallSize)
{
	sf::RectangleShape wallObject;
	wallObject.setPosition(sf::Vector2f(float(wallPosition.x - (double)wallSize.width/2.L), float(wallPosition.y - (double)(wallSize.height/2.L))));
	wallObject.setSize(sf::Vector2f((float)wallSize.width, (float)wallSize.height));

	sf::RectangleShape oldYObject;
	oldYObject.setPosition(sf::Vector2f(float(lastPosition.x - (double)objectSize.width/2.L), float(positionToRevert.y - (double)(objectSize.height/2.L))));
	oldYObject.setSize(sf::Vector2f((float)objectSize.width, (float)objectSize.height));

	sf::RectangleShape oldXObject;
	oldXObject.setPosition(sf::Vector2f(float(positionToRevert.x - (double)objectSize.width/2.L), float(lastPosition.y - (double)(objectSize.height/2.L))));
	oldXObject.setSize(sf::Vector2f((float)objectSize.width, (float)objectSize.height));

	if (collision::areColliding(wallObject, oldYObject))
	{
		positionToRevert.y = lastPosition.y;
	}
	if (collision::areColliding(wallObject, oldXObject))
	{
		positionToRevert.x = lastPosition.x;
	}
}