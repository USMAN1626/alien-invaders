#include "Entity.h";

Entity::Entity(sf::Texture& texture)
{
	sprite.setTexture(texture);  // Set the entity's texture
}



void Entity::setPosition(float x, float y)
{
	sprite.setPosition(x, y);  // Set the entity's position
}

Entity::~Entity()
{
}

sf::Vector2f Entity::getPosition()
{
	return sprite.getPosition();  // Get the entity's position
}

