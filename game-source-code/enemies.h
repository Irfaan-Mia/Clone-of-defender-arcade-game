#ifndef ENEMIES_H
#define ENEMIES_H

/**
 * @file enemies.h
 * @brief This class is a parent class to pods, aliens and asteriods classes. Reponsible for movement, collision detection, spawning and checking endgame conditions. 
 * @version 0.1
 * @date 2023-10-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include <vector> 
#include <utility> // for std::pair
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "landersMissiles.h"
#include "projectiles.h"
#include "score.h"
#include "playerShip.h"
#include "playerShield.h"
#include "playerLives.h"

class playerShip; // Forward declaration of the ship class
class enemy {
public:
    /**
    * @brief Construct a new enemy object.
    * 
    */
    enemy();
    /**
     * @brief Destroy the enemy object.
     * 
     */
    virtual ~enemy();
    /**
     * @brief Initializes enemy sprite with respective texture and random spawn position.
     * 
     */
    virtual void createEnemy();
    /**
     * @brief Addes new enemy to vector of sf::Sprite objects.
     * 
     * @param enemy sf::Sprite representing enemy type.
     */
    void addEnemy(sf::Sprite enemy);
    /**
     * @brief Create a random direction of movement for the new enemy.
     * 
     */
    virtual void enemyDirection();
    /**
     * @brief Moves all enemy sf::Sprite objects within vector of sf::Sprite objects.
     * 
     */
    virtual void moveEnemies(); 
    /**
     * @brief Spawns a new enemy if timer has elapsed and max enemies have not been reached.
     * 
     */
    virtual void spawnEnemy();
    /**
     * @brief Returns vector of all enemy sf::Sprite objects created. 
     * 
     * @return std::vector<sf::Sprite>& vecotr of sf::Sprite objects represeting enemies.
     */
    std::vector<sf::Sprite>& getEnemySprites();
    /**
     * @brief Checks if player has a collision with enemies.
     * 
     * @param playerShip_ PlayerShip object.
     * @return true if there is a collision.
     * @return false if there is no collision.
     */
    bool hasPlayerCollision(playerShip &playerShip_);
    /**
     * @brief Checks if player has a collision with enemies and completes required steps.
     * 
     * @param playerShip_ PlayerShip class object.
     */
    void checkPlayerCollision(playerShip &playerShip_);
    /**
     * \brief Check players projectile collision with pods.
     * 
     * \param playershipProjectiles_ vector of playerships projectiles objects.
     */
    virtual void checkProjectileCollision(std::vector<projectiles>& playershipProjectiles_);
    /**
     * @brief Updates the spawning and movement of all enemies. 
     * 
     */
    void updateEnemies();
    /**
     * @brief Sets the change in time value required for movement.
     * 
     * @param deltaTime_ float value of change in time.
     */
    void setDeltaTime(float deltaTime_);
    /**
     * @brief Set the Players Position variable.
     * 
     * @param playersPosition_ sf::Vector2f containing x and y coordinates of player position.
     */
    void setPlayersPosition(sf::Vector2f playersPosition_);
    /**
     * @brief Checks if all enemies have been eliminated.
     * 
     * @return true if all enemies eliminated.
     * @return false if all enemies have not been eliminated.
     */
    bool defeatedEnemies();
    /**
     * @brief Returns x and y directions of all enemies
     * 
     * @return std::pair<std::vector<float>, std::vector<float>> vector of x and y directions of all enemies.
     */
    std::pair<std::vector<float>, std::vector<float>> getXAndYDirections();

protected:
    /**
     * @brief Checks collision of new enemy being spawned to exisiting enemies.
     * 
     * @param newEnemy_ sf::Sprite of new enemy being spawned
     * @param existingEnemies_ vector of sf::Sprite containing currently spawned enemies
     * @return true if there is a collision 
     * @return false if there is no collision
     */
    bool checkCollision(const sf::Sprite& newEnemy_, const std::vector<sf::Sprite>& existingEnemies_);
    /**
     * @brief Checks if the timer for spawning new enemies has elapsed
     * 
     * @return true if spawn timer has elapsed required time. 
     * @return false if spawn timer has not elapsed required time.
     */
    bool checkSpawnTimer();
    /**
     * @brief Checks if space of new enemy spawn in available. 
     * 
     * @param randX_ float value of x coordinate.
     * @param randY_ float value of y coordinate.
     * @return true if the space is available.
     * @return false if the space is unavailable.
     */
    bool checkSafeSpawn(float randX_, float randY_);

    sf::Clock clock_;
    sf::Texture enemyTexture_;
    std::vector<sf::Sprite> enemies_;
    std::vector<float> xDirections_;
    std::vector<float> yDirections_;
    sf::Sound collisionSound_;
    sf::SoundBuffer collisionSoundBuffer_;
    int enemyCounter_ = 0;
    int maxEnemies_;
    float dt_;
    float enemySpeed_;
    float enemyspawnInterval_;
    float previousTime_; 
    float enemySpawnOffset = 30.0f;
    sf::Vector2u windowSize_{3000, 750};
    sf::Vector2f enemyScale_;
    sf::Vector2f playerPosition_;
    float pi = 3.14159; 

};

#endif