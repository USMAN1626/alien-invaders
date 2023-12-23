#pragma once
#include"Entity.h"
#include <SFML/Graphics.hpp>  // Include the SFML graphics library
#include <cstdlib>  // Include the C standard library for rand() and srand()
#include <ctime>  // Include the C time library for time()
#include <vector>  // Include the vector container
#include<windows.h>

class Player:public Entity
{
public:
    const int screenWidth = 800;  // Define the screen width
    int health = 100,score=0,level=0, playerSpeed = 5;
    Player(sf::Texture& texture) : Entity(texture) {};
    void update() override;
    ~Player();
};

