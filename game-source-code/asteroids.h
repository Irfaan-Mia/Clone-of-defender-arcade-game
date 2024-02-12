#ifndef ASTEROIDS_H
#define ASTEROIDS_H

/**
 * @file asteroids.h
 * @brief This class is responsible for spawning, moving and displaying asteriods.
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "enemies.h"
#include "landersMissiles.h"
#include "playerShip.h"
#include "playerShield.h"

class asteroids : public enemy
{
    public: 
    /**
     * @brief Construct a new asteroids object and initializes required textures, sound buffers and vital parameters from parent class. 
     * 
     */
    asteroids();
    /**
     * @brief Destroy the asteroids object
     * 
     */
    ~asteroids();
    /**
     * @brief Initializes and adds a maximum number of sf::Sprite objects representing asteriods to vector of sf::Sprite objects within Parent class 
     * 
     */
    void createEnemy() override;
    /**
     * @brief Spawns vector of sf::Sprite objects representing asteriods if enough time has elapsed 
     * 
     */
    void spawnEnemy() override;
    /**
     * @brief Initializes direction of movement of each sf::Sprite object representing an asteriod
     * 
     */
    void enemyDirection() override;
    /**
     * @brief Moves each sf::Sprite object from Parent class representing an asteriod in a random swaps sign of x-axis direction of each sf::Sprite object within Parent class 
     * 
     */
    void moveEnemies() override;
    /**
     * @brief Resets Asteriods class to default state
     * 
     */
    void resetAsteroids();
    /**
     * @brief Displays vector of sf::Sprite objects within render window 
     * 
     * @param window_ Reference to sf::RenderWindow object. 
     */
    void displayAsteroids(sf::RenderWindow& window_);

private: 
    int asteroidCounter_ = 0;
    int totalAsteroids_ = 1;
    int asteroidSpeed_ = 70.00f;
    float spawnInterval_ = 5000;
    const float pi = 3.14159;
    
    //Frame rate control
    float dt; 
};

#endif 
