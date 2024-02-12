#ifndef LANDERS_MISSILES_H
#define LANDERS_MISSILES_H

/**
 * @file landersMissiles.h
 * @brief This class is responsible for handling the shooting, moving and checking border collisions of aliens projectiles. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include "projectiles.h"
#include <cmath>
#include <vector>
#include <iostream> 

class landersMissiles
{
    public: 
    /** \brief Constructor.

    Creates a landersMissiles object and initializes required textures.
    */ 
    landersMissiles();

    /** \brief Destructor.

     Destroys a landerMissiles object.
    */
    ~landersMissiles();

    /** \brief Add new landerMissile into vector and calculates angle.

        Calculates angle between the lander and player current position to determine direction and adds the new 
        bullet.

    \param landersPosition sf::Vector2f containing x and y coordinate of enemies current location.
    \param playerPosition sf::Vector2f containing x and y coordinate of players current location.
    */
    void addlanderMissile(sf::Vector2f landersPosition, sf::Vector2f playersPosition);

    /** \brief Returns vector containing bullets.

        Returns the sprite of bullets that have been made and pushed into the vector.
    \return vector of sf::Sprites representing aliens projectiles. 
    */
    std::vector<projectiles>& getbullets();

    /** \brief Processes direction for bullets.

        Calculate direction bullet needs to move in direction of the player.

    */
    void moveBullets();

    /** \brief Removes bullet.

        Deletes bullet at corresponding index.

    \param index const integer of the position of bullet within vector that is removed .
    */
    void removeBullet(const int& index);

    /** \brief Display.

       Displays the current bullets shot by landers in the new positions.

    \param window Reference to sf::RenderWindow object.
    */
    void draw(sf::RenderWindow& window);

    /** \brief Resets landers missiles.

        Resets the landers missiles to initia state. 

    */
    void resetLandersMissiles();

    /** \brief Sets players positions.

        Sets players x and y coordinates for landers missile trajectory calculation.

    \param Position_ sf::Vector2f containing x and y coordinates of the players ship.
    */
    void setplayerPosition(sf::Vector2f Position_);

    /** \brief Sets delta time.

        Sets the change in time so movement independent of framerate. 

    \param deltaTime float value of change in time. 
    */
    void setdt(float deltaTime);
    
    private:
    std::vector<sf::Sprite> convertLanderMissilesToSprites();

    std::vector<projectiles> landersMissiles_; 
    std::vector<sf::Sprite> bullets; 
    sf::Texture bullet_texture; 
    std::vector<float> angle; 
    sf::Vector2f playersPosition_; 
    float movementSpeed_{100.0f};

    //Frame rate control
    float dt;
};

#endif 