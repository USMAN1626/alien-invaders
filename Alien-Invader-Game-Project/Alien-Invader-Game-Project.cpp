#include"Entity.h"
#include"Bullet.h"
#include"Enemy.h"
#include"Player.h"
#include <SFML/Graphics.hpp>  // Include the SFML graphics library
#include<SFML/Audio.hpp>
#include <cstdlib>  // Include the C standard library for rand() and srand()
#include <ctime>  // Include the C time library for time()
#include <vector>  // Include the vector container
#include<windows.h>
#include<iostream>
#include<stack>

const int screenWidth = 800;  // Define the screen width
const int screenHeight = 600;  // Define the screen height
const int bulletSpeed = 10;  // Define the bullet's movement speed



// Function to check collision between two sprites
bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());  // Check if the two sprites intersect
}

int main() {
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Space Invaders");  // Create the game window
    window.setFramerateLimit(60);  // Limit the frame rate

    sf::Texture playerTexture, bulletTexture, enemyTexture, backgroundTextureLevel1, backgroundTextureLevel2, backgroundTextureLevel3, winBG, loseBG;  // Declare texture variables
    playerTexture.loadFromFile("player1.png");  // Load the player's texture from file
    bulletTexture.loadFromFile("bullet.png");  // Load the bullet's texture from file
    enemyTexture.loadFromFile("UFO.png");  // Load the enemy's texture from file
    backgroundTextureLevel1.loadFromFile("background1.png");// Load the background texture from file
    backgroundTextureLevel2.loadFromFile("background2.png");// Load the background texture from file
    backgroundTextureLevel3.loadFromFile("background3.png");// Load the background texture from file
    winBG.loadFromFile("winbg.png");
    loseBG.loadFromFile("losebg.png");
    Player player(playerTexture);  // Create a player object
    player.setPosition(screenWidth / 2 - player.sprite.getGlobalBounds().width / 2, screenHeight - player.sprite.getGlobalBounds().height - 10);  // Set the player's initial position

    std::vector<Bullet> bullets;  // Create a vector to hold the bullets
    std::vector<Enemy> enemies;  // Create a vector to hold the enemies

    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Seed the random number generator

    sf::SoundBuffer fireSound;
    sf::Sound fSound;
    fireSound.loadFromFile("fire.wav");
    fSound.setBuffer(fireSound);

    sf::SoundBuffer endSound;
    sf::Sound eSound;
    endSound.loadFromFile("end.wav");
    eSound.setBuffer(endSound);

    sf::SoundBuffer healthSound;
    sf::Sound hSound;
    healthSound.loadFromFile("healthd.wav");
    hSound.setBuffer(healthSound);

    sf::SoundBuffer loseSound;
    sf::Sound LoseSound;
    loseSound.loadFromFile("lose.wav");
    LoseSound.setBuffer(loseSound);

    sf::SoundBuffer winSound;
    sf::Sound WinSound;
    winSound.loadFromFile("win.wav");
    WinSound.setBuffer(winSound);

    sf::Font font;
    font.loadFromFile("Bebas.otf");

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    sf::Text playerHealth;
    playerHealth.setFont(font);
    playerHealth.setCharacterSize(24);
    playerHealth.setFillColor(sf::Color::Red);
    playerHealth.setPosition(screenWidth - 150, 10);

    sf::Sprite backgroundSprite(backgroundTextureLevel1);  // Create background sprite for level1
    sf::Sprite backgroundSprite2(backgroundTextureLevel2);  // Create background sprite for level2
    sf::Sprite backgroundSprite3(backgroundTextureLevel3);  // Create background sprite for level3
    sf::Sprite winbg(winBG);
    sf::Sprite losebg(loseBG);
    std::stack<sf::Sprite> backgroundStack;
    backgroundStack.push(backgroundSprite3);  // Push the background sprite for level 3
    backgroundStack.push(backgroundSprite2);  // Push the background sprite for level 2
    backgroundStack.push(backgroundSprite);  // Push the background sprite for level 1


    while (window.isOpen()) {
        bool isShooting = false;  // Flag to track if the player is shooting

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();  // Close the window if the close button is clicked
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space && !isShooting) {
                    // Create a new bullet and add it to the bullets vector
                    fSound.play();
                    Bullet bullet(bulletTexture);
                    bullet.setPosition(player.getPosition().x + player.sprite.getGlobalBounds().width / 2 - bullet.sprite.getGlobalBounds().width / 2, player.getPosition().y);
                    bullet.velocity = sf::Vector2f(0, -bulletSpeed);
                    bullets.push_back(bullet);
                    isShooting = true;
                }
            }

        }

        // ...

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.velocity.x = -player.playerSpeed;  // Move the player left
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.velocity.x = player.playerSpeed;  // Move the player right

        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.velocity.x = 0;  // Stop the player's movement

        // ...

        if (isShooting) {
            // Update the position of the bullets and remove them if they go off-screen
            for (int i = bullets.size() - 1; i >= 0; --i) {
                bullets[i].update();
                if (bullets[i].getPosition().y < 0) {
                    bullets.erase(bullets.begin() + i);
                }
            }
        }

        if (enemies.size() < 5) {
            int randomX = std::rand() % (screenWidth - enemyTexture.getSize().x);  // Generate a random x-coordinate for the enemy
            // Create a new enemy and add it to the enemies vector
            Enemy enemy(enemyTexture);
            enemy.setPosition(randomX, 0);
            if (player.score > 10 && player.score < 20) {
                enemy.enemySpeed += 0.5;
            }
            else if (player.score > 20 && player.score < 30) {
                enemy.enemySpeed += 0.5;
            }
            else if (player.score > 30 && player.score < 40) {
                enemy.enemySpeed += 0.6;
            }
            else if (player.score > 40 && player.score < 50) {
                enemy.enemySpeed += 0.8;
            }
            enemy.velocity = sf::Vector2f(0, enemy.enemySpeed);
            enemies.push_back(enemy);
        }



        // Update the position of the bullets and remove them if they go off-screen or collide with enemies
        for (int i = bullets.size() - 1; i >= 0; --i) {
            bullets[i].update();
            if (bullets[i].getPosition().y < 0) {
                bullets.erase(bullets.begin() + i);
                isShooting = false;  // Reset isShooting when the bullet goes off-screen
            }
            else {
                for (int j = enemies.size() - 1; j >= 0; --j) {
                    if (checkCollision(bullets[i].sprite, enemies[j].sprite)) {
                        bullets.erase(bullets.begin() + i);
                        enemies.erase(enemies.begin() + j);
                        eSound.play();
                        isShooting = false;  // Reset isShooting when a collision occurs
                        player.score++;
                        break;
                    }
                }
            }
        }


        // Update the position of the enemies and remove them if they go off-screen
        for (int i = enemies.size() - 1; i >= 0; --i) {
            enemies[i].update();
            if (enemies[i].getPosition().y > screenHeight) {
                enemies.erase(enemies.begin() + i);
                player.score--;
                hSound.play();
                if (player.score <= 0) {

                    window.draw(winbg);
                    LoseSound.play();
                    Sleep(3000);
                    window.close();
                }
            }
            if (checkCollision(player.sprite, enemies[i].sprite)) {
                player.health -= 20;// Decrease player health when hit by an enemy
                hSound.play();
                if (player.health <= 0) {

                    // Game over condition
                    window.draw(losebg);
                    LoseSound.play();
                    Sleep(3000);
                    window.close();
                }
                enemies.erase(enemies.begin() + i);
            }

            // Check for collisions between bullets and enemies
            for (int j = bullets.size() - 1; j >= 0; --j) {
                if (checkCollision(bullets[j].sprite, enemies[i].sprite)) {
                    bullets.erase(bullets.begin() + j);
                    enemies.erase(enemies.begin() + i);
                    player.score++;
                    break;
                }
            }
        }

        player.update();  // Update the player's position

        window.clear();  // Clear the window



        if (player.score == 11 && !backgroundStack.empty()) {
            backgroundStack.pop();
            player.score += 1;

        }

        else if (player.score == 31 && !backgroundStack.empty()) {
            backgroundStack.pop();
            player.score += 1;

        } // Draw the background when level gets 3
        window.draw(backgroundStack.top());
        if (player.score == 51 && !backgroundStack.empty())
        {
            window.draw(winbg);
            WinSound.play();
            window.close();
        }


        window.draw(player.sprite);  // Draw the player's sprite


        for (const auto& bullet : bullets)
            window.draw(bullet.sprite);  // Draw each bullet's sprite

        for (const auto& enemy : enemies)
            window.draw(enemy.sprite);  // Draw each enemy's sprite

        scoreText.setString("Score: " + std::to_string(player.score));
        window.draw(scoreText);

        playerHealth.setString("Health: " + std::to_string(player.health));
        window.draw(playerHealth);

        window.display();  // Display the contents of the window
    }

    return 0;
}

