#ifndef POD_H
#define POD_H

/** \file pod.h
    \brief Contains code all things pod enemy related.
*/

/* Header Files */
#include "enemies.h"
#include "score.h"
#include "playerShield.h"
#include "playerLives.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

class pod : public enemy {
public: 
    /**
     * \brief Construct a new pod object
     * 
     */
    pod();
    /**
        \brief Destroy the pod object
     */
    ~pod();
    /**
     * \brief Checks swarm collision with player
     * 
     * \param playership_ ship object of player 
     */
    void checkSwarmCollision(playerShip &playership_);
    /**
     * \brief Check players projectile collision with pods
     * 
     * \param playershipProjectiles_ vector of playerships projectile
     */
    void checkProjectileCollision(std::vector<projectiles>& playershipProjectiles_) override;
    /**
     * \brief Check players projectile collision with swarm
     * 
     * \param playershipProjectiles_ vector of playerships projectile
     */
    void checkSwarmProjectileCollision(std::vector<projectiles>& playershipProjectiles_);
    /**
     * \brief Spawns swarm on specified position
     * 
     * \param podPosition_ Eliminated pods position
     */
    void spawnSwarm(sf::Vector2f podPosition_);
    /**
     * \brief Get the Swarm Sprites object
     * 
     * \param std::vector<sf::Sprite>& of existing swarm within game screen
     */
    std::vector<sf::Sprite>& getSwarmSprites();
    /**
     * \brief Moves swarm toward player 
     */
    void moveSwarm();
    /**
     * \brief Updates pods 
     */
    void updatePods();
    /**
     * \brief Displays swarm and pods 
     * 
     * \param window_ Reference to sf::RenderWindow object.
     */
    void display(sf::RenderWindow& window_);
    /**
     * \brief Resets pods to initial state
     */
    void resetPods();
    /**
     * \brief Resets spawn timer of pods 
     */
    void resetSpawnTimer();

private:
    void addSwarmEnemy(sf::Vector2f position);
    std::vector<sf::Sprite> pods_;
    sf::Sprite swarmSprite_;
    sf::Texture podTexture_; 
    sf::Texture swarmTexture_;
    sf::Vector2f podScale_{1.3f,1.3f};
    std::vector<sf::Sprite> swarm_;
    int totalEnemies_ = 3;
    int enemySpeed_ = 70.00f;
    float spawnInterval_ = 5000;
    int swarmSpeed_ = 200.00f;
    const float pi = 3.14159;
    sf::SoundBuffer swarmSoundBuffer_;
    sf::Sound swarmSound_;


    // Players score
    int podPoints_ = 1000;
    int swarmPoints_ = 150; 
    score playerScore_;  

    //Frame rate control
    float dt; 
};

#endif // POD_H