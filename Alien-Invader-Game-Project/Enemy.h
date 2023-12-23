#pragma once

#include"Entity.h"
#include <SFML/Graphics.hpp>  // Include the SFML graphics library
#include <cstdlib>  // Include the C standard library for rand() and srand()
#include <ctime>  // Include the C time library for time()
#include <vector>  // Include the vector container
#include<windows.h>

class Enemy :public Entity
{
public:
    float enemySpeed = 0.75;
    Enemy(sf::Texture& texture) : Entity(texture) {}  // Constructor

    void update() override;
    ~Enemy();
};

