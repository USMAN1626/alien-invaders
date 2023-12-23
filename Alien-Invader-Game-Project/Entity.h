#pragma once
#include <SFML/Graphics.hpp>  // Include the SFML graphics library
#include <cstdlib>  // Include the C standard library for rand() and srand()
#include <ctime>  // Include the C time library for time()
#include <vector>  // Include the vector container
#include<windows.h>

class Entity
{
public:
    sf::Sprite sprite;  // Sprite object for the entity
    sf::Vector2f velocity;  // Velocity vector for the entity's movement
    sf::Vector2f getPosition();
    Entity(sf::Texture& texture);
    void setPosition(float x, float y);
    virtual void update() = 0;
    ~Entity();
};