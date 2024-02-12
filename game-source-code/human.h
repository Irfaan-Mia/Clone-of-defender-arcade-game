#ifndef HUMAN_H
#define HUMAN_H

/**
 * @file human.h
 * @brief This class is responsible for spawning, moving and displaying humanoids. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include "alien.h"
#include "score.h"
#include "playerShield.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>


class human
{
    public: 
    /**
     * @brief Construct a new human object and initializes required textures. 
     * 
     */
    human();
    /**
     * @brief Destroy the human object.
     * 
     */
    virtual ~human();
    /**
     * @brief Set the Delta Time variable.
     * 
     * @param deltaTme float value representing the change in time.
     */
    void setDeltaTme(float deltaTme);
    /**
     * @brief Adds a humanoid sprite object. 
     * 
     * @param humanoid_ sf::Sprite object representing humanoid.
     */
    void addHumanoid(sf::Sprite humanoid_);
    /**
     * @brief Returns a vector of humanoids x and y coordinates.
     * 
     * @return std::vector<sf::Vector2f> vector of sf::Vector2f containing x and y coordinates of each humanoid.
     */
    std::vector<sf::Vector2f>  humanoidsPositions();
    /**
     * @brief Resets humanoids to initial state.
     * 
     */
    void resetHumanoids();
    
    protected:
    /**
     * @brief Updates spawn of humanoids.
     * 
     */
    void updateHumanoids();
    /**
     * @brief Displays vector of sf::Sprites.
     * 
     * @param entities vector of sf::Sprite objects required to display.
     * @param window Reference to RenderWindow object.
     */
    void displayGameEntities(std::vector<sf::Sprite>& entities, sf::RenderWindow& window);
    /**
     * @brief Checks collision between humanoids.
     * 
     * @param newHumanoid_ sf::Sprite representing New humanoid being spawned.
     * @param existingHumanoids_ vector of sf::Sprite objects representing currently spawned humanoids.
     * @return true if new humanoid being spawned collides with currently spawned humanoid.
     * @return false if new humanoid being spawned does not collide with currently spawned humanoid.
     */
    bool checkCollision(const sf::Sprite& newHumanoid_, const std::vector<sf::Sprite>& existingHumanoids_); 
    /**
     * @brief Moves specific humanoids.
     * 
     * @param index vector of integers represnting indices of specific humanoids. 
     * @param speed float value representing speed and direction of specific humanoids movement.
     */
    void moveHumanoid(std::vector<int>& index, float speed);
    /**
     * @brief Get the Humanoids sf::Sprite objects.
     * 
     * @return std::vector<sf::Sprite>& vector of sf::Sprite objects representing currently spawned humanoids.
     */
    std::vector<sf::Sprite>& getHumanoids();
    /**
     * @brief Checks if all humanoids are spawned.
     * 
     * @return true if all humanoids spawned.
     * @return false if all humanoids not spawned. 
     */
    bool checkHumanoidCounter();

    float dt_; 

    private: 
    void createHumanoid();
    void spawnHumanoid();

    std::vector<sf::Sprite> humanoids_;
    int humanoidCounter_ = 0;
    int totalHumanoids_ = 5;
    sf::Texture humanoidTexture_; 
    sf::Vector2f humanoidScale_{0.05f,0.05f};
    float spawnInterval_ = 1000;
    const float pi = 3.14159;
    float previousTime_; 
    float enemySpawnOffset = 30.0f;
    sf::Vector2u windowSize_{1350, 750};


};

#endif