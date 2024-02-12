#ifndef ALIEN_H
#define ALIEN_H

/**
 * @file alien.h
 * @brief This class is responsible for handling the spawning, collisions, movement and displaying of enemy type alien.
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
#include "playerLives.h"

class alien: public enemy
{
    public:
    /**
     * @brief Construct alien object. Initializes aliens texture and sound buffer. Sets default parameters from inherited parent class. 
     * 
     */
    alien();
    /**
     * @brief Destroy the alien object.
     * 
     */
    ~alien();
    /**
     * @brief Retrieves the Landers Missiles vector of projetile class objects.
     * 
     * @return std::vector<projectiles>& vector containing projectile class objects of landers missiles. 
     */
    const std::vector<projectiles>& getLandersMissiles();
    /**
     * @brief Checks for a collision between a vector of 'projectiles' class objects spawned by the player's ship with spawned alien objects.
     * 
     * @param playershipProjectiles_ std::vector<projectiles> vector of projectiles class objects. 
     * @return true if there is a collision between an alien object and projectiles object.
     * @return false if there is no collision between an alien object and projectiles object.
     */
    bool hasProjectileCollision(std::vector<projectiles> &playershipProjectiles_);
    /**
     * @brief Checks for a collision between a vector of 'projectiles' class objects spawned by the player's ship with spawned alien objects.
     * 
     * @param playershipProjectiles_ std::vector<projectiles> vector of projectiles class objects.
     */
    void checkProjectileCollision(std::vector<projectiles> &playershipProjectiles_) override;
    /**
     * @brief Checks if the aliens vector of sprites objects from LandersMissiles class collides with the player's PlayerShip object.
     * 
     * @param playerShip_ PlayerShip object. 
     * @return true if there is a collision with an aliens LandersMissiles objects and PlayerShip object.
     * @return false if there is no collision.
     */
    bool hasMissilesCollision(playerShip& playerShip_);
    /**
     * @brief Checks if the aliens vector of sprites objects from LandersMissiles class collides with the player's PlayerShip object.
     * 
     * @param playerShip_ playership object.
     */
    void checkMissilesCollision(playerShip &playerShip_);
    /**
     * @brief Resets aliens object to initial state.
     * 
     */
    void resetAliens();
    /**
     * @brief Resets spawn timer of aliens object.
     * 
     */
    void resetSpawnTimer();
    /**
     * @brief Deletes a alien landerMissile object from LanderMissiles objects.
     * 
     * @param index_ integer value for position of landerMissile object within LanderMissiles objects.
     */
    void removeLandersMissile(const int& index_);
    /**
     * @brief If specific amount of time has elapsed all aliens spawned will shoot a projectile. 
     * 
     */
    void shootbullets();
    /**
     * @brief Adds new landerMissile sprite object to LanderMissiles object.
     * 
     * @param enemy_ sf::Sprite object representing aliens projectiles.
     */
    void addBullet(sf::Sprite enemy_);
    /**
     * @brief Displays the aliens spawned within game screen and LanderMissiles classes vector of sprite objects.
     * 
     * @param window_ Reference to sf::RenderWindow object. 
     */
    void display(sf::RenderWindow& window_);

private: 
    landersMissiles landersBullets_;
    float shootingInterval_ = 5000.0f;
    int totalEnemies_ = 10;
    int enemySpeed_ = 70.00f;
    float spawnInterval_ = 1000;
    const float pi = 3.14159;

    // Players score
    int alienPoints_ = 150;
    score playerScore_;  
    
    //Frame rate control
    float dt; 
};

#endif 
