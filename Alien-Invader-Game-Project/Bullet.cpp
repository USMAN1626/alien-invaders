#include "Bullet.h"

void Bullet::update()
{
	sprite.move(velocity);  // Move the bullet's sprite based on the velocity
}

Bullet::~Bullet()
{
}
