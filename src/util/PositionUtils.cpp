#include "util/PositionUtils.hpp"
#include "util/OverlapUtils.hpp"

#include "util/Position.hpp"
#include "util/Size.hpp"
#include <math.h>

#include <iostream>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFMLUtil/Graphics/RectangularBoundaryCollision.hpp>

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
	wallObject.setPosition(sf::Vector2f(wallPosition.x - wallSize.width/2, wallPosition.y - wallSize.height/2));
	wallObject.setSize(sf::Vector2f(wallSize.width, wallSize.height));

	sf::RectangleShape oldYObject;
	oldYObject.setPosition(sf::Vector2f(lastPosition.x - objectSize.width/2, positionToRevert.y - objectSize.height/2));
	oldYObject.setSize(sf::Vector2f(objectSize.width, objectSize.height));

	sf::RectangleShape oldXObject;
	oldXObject.setPosition(sf::Vector2f(positionToRevert.x - objectSize.width/2, lastPosition.y - objectSize.height/2));
	oldXObject.setSize(sf::Vector2f(objectSize.width, objectSize.height));

	if (collision::areColliding(wallObject, oldYObject))
	{
		positionToRevert.y = lastPosition.y;
	}
	if (collision::areColliding(wallObject, oldXObject))
	{
		positionToRevert.x = lastPosition.x;
	}
}