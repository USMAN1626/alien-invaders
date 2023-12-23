#include "Player.h"
void Player::update()
{
    sprite.move(velocity);  // Move the player's sprite based on the velocity

    // Prevent the player from moving off the screen
    if (sprite.getPosition().x < 0)
        sprite.setPosition(0, sprite.getPosition().y);
    if (sprite.getPosition().x > screenWidth - sprite.getGlobalBounds().width)
        sprite.setPosition(screenWidth - sprite.getGlobalBounds().width, sprite.getPosition().y);
}

Player::~Player()
{
}
