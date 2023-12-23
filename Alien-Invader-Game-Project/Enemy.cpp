#include "Enemy.h"

void Enemy::update()
{
	sprite.move(velocity);  // Move the enemy's sprite based on the velocity
}

Enemy::~Enemy()
{
}
