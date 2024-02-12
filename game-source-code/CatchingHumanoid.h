#ifndef CATCHINGHUMANOID_H
#define CATCHINGHUMANOID_H

/**
 * @file CatchingHumanoid.h
 * @brief This class is responsible for handling the events of a falling humanoid being caught by the player and being returned to the ground.
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include "playerShip.h"

class catchingHumanoid
{
    public:
    /**
     * @brief Construct a catching Humanoid object
     * 
     */
    catchingHumanoid();
    /**
     * @brief Destroy the catching Humanoid object
     * 
     */
    ~catchingHumanoid();
    /**
     * @brief Checks if falling humanoid and playership collide. If collision necessary actions completed 
     * 
     * @param playerPos sf::FloatRect containing x and y coordinates of the player
     * @param humanoids_ vector of sf::Sprite containing all the humanoids sf::Sprite objects 
     * @param fallingHumanoidsIndex vector of integers representing indices of falling humanoids
     * @param caughtHumanoidIndex integer representing index of caught humanoid 
     */
    void checkHumanoidCaught(sf::FloatRect playerPos,std::vector<sf::Sprite>&humanoids_,std::vector<int>&fallingHumanoidsIndex,int&caughtHumanoidIndex);
    /**
     * @brief Moves caught humanoid with players ship 
     * 
     * @param humanoids_ vector of sf::Sprite containing all the humanoids sf::Sprite objects 
     * @param caughtHumanoidIndex integer representing index of caught humanoid
     */
    void moveHumanoidwithPlayer(std::vector<sf::Sprite>&humanoids_,int&caughtHumanoidIndex);
    /**
     * @brief Checks if caught humanoid returned to the ground safely
     * 
     * @param humanoids_ vector of integers representing indices of falling humanoids
     * @param caughtHumanoidIndex integer representing index of caught humanoid
     */
    void checkHumanoidSafe(std::vector<sf::Sprite>&humanoids_,int&caughtHumanoidIndex);
    /**
     * @brief Sets players position 
     * 
     * @param playerPos sf::Vector2f containing x and y coordinates of player position
     */
    void setplayerPos(sf::Vector2f playerPos);
    private:
    sf::Vector2f playerPos_; 
};

#endif