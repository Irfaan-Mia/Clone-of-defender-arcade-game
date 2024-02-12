#ifndef PLAYERPROJECTILES_H
#define PLAYERPROJECTILES_H

/**
 * @file PlayerProjectiles.h
 * @brief This class is responsible for processing user input, adding a player projectile, wrapping projectile around screen and checking collision of projectile with game borders. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream> 
#include "projectiles.h"

class PlayerProjectiles
{
    public:
    /**
     * @brief Construct a new Player Projectiles object.
     * 
     */
    PlayerProjectiles();
    /**
     * @brief Destroy the Player Projectiles object.
     * 
     */
    ~PlayerProjectiles();
    /**
     * @brief Processes input from user
     * 
     * @param direction sf::Vector2f representing x and y direction of the player. 
     * @param PlayerPos sf::Vector2f representing x and y position of the player.
     * @param keyPressed sf::Keyboard::key Specific key pressed by the user. 
     */
    void processEvent(sf::Vector2f direction, sf::Vector2f PlayerPos, sf::Keyboard::Key keyPressed);
    /**
     * @brief Adds player projectile.
     * 
     * @param direction sf::Vector2f representing x and y direction of the player.
     * @param PlayerPos sf::Vector2f representing x and y position of the player.
     * @param keyPressed sf::Keyboard::Key Specific key pressed by the user.
     */
    void shootbullet(sf::Vector2f direction, sf::Vector2f PlayerPos, sf::Keyboard::Key keyPressed);
    /** \brief Update the player's projectile.

     Updates the projectiles current position to new position and removes bullets out of screen.
    */
    void update();
    /**
     * @brief Sets delta time.
     * 
     * @param deltaTime float value of the change in time.
     */
    void setdt(float deltaTime);
    /**
     * @brief Borders where player projectile is allowed.
     * 
     * @param LeftBorder_ sf::RectangleShape representing Left game border. 
     * @param RightBorder_ sf::RectangleShape representing Right game border.
     */
    void setprojectileBorder(sf::RectangleShape& LeftBorder_, sf::RectangleShape& RightBorder_);
    /**
     * @brief Resets player projectiles.
     * 
     */
    void resetProjectiles();
    /** \brief Returns players projectiles.

        Returns all the projectiles that the player shot.  

    \return Returns vector of projectiles object.
    */
    std::vector<projectiles>& getPlayerProjectiles();
    /**
     * @brief Displays player projectiles.
     * 
     * @param window Reference to sf::RenderWindow object.
     */
    void display(sf::RenderWindow& window);
    /**
     * @brief Number of players projectiles.
     * 
     * @return int value of existing players projectiles.
     */
    int numberProjectiles();
    private:
    void checkProjectileCollisionBorder(sf::RectangleShape& LeftBorder_, sf::RectangleShape& RightBorder_);
    void wrapProjectile(projectiles& bullet);

    std::vector<projectiles> playerProjectiles_; 
    float bulletspeed_ = 800.0f;
    float dt_;
    float previousTime_;
    float maxgameView_ = 3000.0f; 
    sf::RectangleShape line1;
    sf::RectangleShape line2;

    sf::Texture projectile_texture; 
    sf::Sound gun_shot; 
    sf::SoundBuffer gun_shot_buffer; 
};

#endif