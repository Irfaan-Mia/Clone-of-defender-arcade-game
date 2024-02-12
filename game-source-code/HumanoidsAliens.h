#ifndef HUMANOIDSALIENS_H
#define HUMANOIDSALIENS_H

/**
 * @file HumanoidsAliens.h
 * @brief  This class is responsible for handling the checking of collisions and stores specific aliens and index of humanoids who are either being tracked, captured, falling or caught. 
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
#include "playerShield.h"
#include "playerLives.h"
#include "score.h"

class humanoidsAliens
{
    public: 
    /**
     * @brief Construct a new humanoids Aliens object.
     * 
     */
    humanoidsAliens(); 
    /**
     * @brief Destroy the humanoids Aliens object.
     * 
     */
    ~humanoidsAliens();
    /**
     * @brief Checks if aliens above any humanoid.
     * 
     * @param alien_ vector of sf::Sprite objects representing aliens vector of sf::Sprite objects.
     * @param humanoids_ vector of sf::Sprite objects representing humanoids.
     */
    void checkalienaboveHumanoid(std::vector<sf::Sprite>& alien_,std::vector<sf::Sprite>& humanoids_);
    /**
     * @brief Checks if the specific humanoids object is available.
     * 
     * @param humanoidIndex integer value of specific humanoids index.
     * @return true if the index is available.
     * @return false if the index is not available.
     */
    bool isHumanoidIndexAvailable(int humanoidIndex);
    /**
     * @brief Checks collision between aliens and humanoids. 
     * 
     * @param alien_ vector of sf::Sprite objects representing aliens vector of sf::Sprite objects.
     * @param humanoids_ vector of sf::Sprite objects representing humanoids.
     */
    void hasAlienCollision(std::vector<sf::Sprite>& alien_, std::vector<sf::Sprite>& humanoids_);
    /**
     * @brief Checks collision between players projectiles and humanoids and landers.
     * 
     * @param humanoids_ vector of sf::Sprite objects representing humanoids.
     * @param humanoidIndexes vector of integers values represnting specific humanoids indices.
     * @param playershipProjectiles_ vector of projectiles class representing players projectiles.
     * @param alien_ alien object.
     */
    void playerProjectileCollision(std::vector<sf::Sprite>& humanoids_,std::vector<int> &humanoidIndexes, std::vector<projectiles> &playershipProjectiles_, alien &alien_);
    /**
     * @brief Checks if captured or falling humanoid hits game borders.
     * 
     * @param humanoids_ vector of sf::Sprite objects representing humanoids.
     * @param aliens_ alien object.
     */
    void checkBorderCollision(std::vector<sf::Sprite> &humanoids_, alien& aliens_);
    /**
     * @brief Checks player collision with aliens.
     * 
     * @param playership PlayerShip object.
     * @param humanoids_ vector of sf::Sprite objects representing humanoids. 
     * @param HumanoidsALiens_ vector of sf::Sprite objects representing humanoids aliens. 
     * @param HumanoidsAliensIndex_ vector of integers representing specific humanoids indices. 
     */
    void checkAlienPlayerShipCollision(playerShip &playership,std::vector<sf::Sprite>& humanoids_,std::vector<sf::Sprite>&HumanoidsALiens_,std::vector<int>&HumanoidsAliensIndex_);
    /**
     * @brief Resets capturing, trakcing and caught landers and humanoids to default.
     * 
     */
    void resetHumanoidsAliens();
    /**
     * @brief Get the Tracking Aliens object.
     * 
     * @return std::vector<sf::Sprite>& vector of sf::Sprites representing tracking aliens. 
     */
    std::vector<sf::Sprite>& getTrackingAliens();
    /**
     * @brief Get the Capturing Aliens object.
     * 
     * @return std::vector<sf::Sprite>& vector of sf::Sprites representing capturing aliens.
     */
    std::vector<sf::Sprite>& getCapturingAliens();
    /**
     * @brief Indices of humanoids captured by landers.
     * 
     * @return std::vector<int>& vector of integers representing captured humanoids indices. 
     */
    std::vector<int>& getcapturedHumanoidIndex();
    /**
     * @brief Indices of falling humanoids 
     * 
     * @return std::vector<int>& vector of integers representing falling humanoids indices. 
     */
    std::vector<int>& getfallingHumanoidsIndex(); 
    /**
     * @brief Indices of tracked humanoids.
     * 
     * @return std::vector<int>& vector of integers representing tracked humanoids indices.
     */
    std::vector<int>& gettrackHumanoidIndex();
    /**
     * @brief Returns specific humanoid index.
     * 
     * @return int& integer value of caught humanoids index. -1 if no caught humanoid.
     */
    int& getcaughtHumanoidIndex(); 

    private: 
    void fixIndices(int index);
    void decrementIndices(std::vector<int>& indices, int index);
    bool checkCollision(const sf::FloatRect object1, const sf::FloatRect object2);
    bool checkAlienAboveHumanoidPos(sf::Sprite human, sf::Sprite enemy);
    bool isIndexAvailable(std::vector<int> index, int humanoidIndex);

    std::vector<sf::Sprite> CapturingAliens; 
    std::vector<sf::Sprite> TrackingAliens; 

    std::vector<int> capturedHumanoidIndex;
    std::vector<int> fallingHumanoidsIndex; 
    std::vector<int> trackingHumanoidIndex;
    int caughtHumanoidIndex = -1; 

    score score_;
    int EliminationHumanoid = -100;
    int AlienScore = 150; 
};

#endif