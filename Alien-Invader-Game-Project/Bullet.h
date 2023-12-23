#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>  // Include the SFML graphics library
#include <cstdlib>  // Include the C standard library for rand() and srand()
#include <ctime>  // Include the C time library for time()
#include <vector>  // Include the vector container
#include<windows.h>

class Bullet :  public Entity
{
public:
   
    Bullet(sf::Texture& texture) : Entity(texture) {}  // Constructor
    void update() override;
    ~Bullet();
};

