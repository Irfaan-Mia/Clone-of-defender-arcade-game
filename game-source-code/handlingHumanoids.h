#ifndef HANDLINGHUMANOIDS_H
#define HANDLINGHUMANOIDS_H

/**
 * @file handlingHumanoids.h
 * @brief This class is reponsible for handling humanoids events such as checking collisions, moving humanoid and alien objects and displaying them. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "human.h"
#include "HumanoidsAliens.h"
#include "CatchingHumanoid.h"

class handlingHumanoids : public human 
{
    public: 
    /**
     * @brief Construct a new handling Humanoids object.
     * 
     */
    handlingHumanoids();
    /**
     * @brief Destroy the handling Humanoids object.
     * 
     */
    ~handlingHumanoids();
    /**
     * @brief Checks collisions with other objects.
     * 
     * @param alien_ Landers object.
     * @param playershipProjectiles_ vector of players projectiles objects.
     * @param playership players ship object.
     */
    void checkCollisions(alien & alien_,std::vector<projectiles> &playershipProjectiles_,playerShip& playership);
    /**
     * @brief Checks if tracking and capturing aliens have been defeated.
     * 
     * @return true if all tracking and capturing aliens have been defeated.
     * @return false if tracking or capturing aliens alive.
     */
    bool checkenemiesDeafeated();
    /**
     * @brief Checks if all the humanoids have been eliminated.
     * 
     * @return true if all the humanoids have been eliminated.
     * @return false if humanoids still alive.
     */
    bool checkallhumansEliminated();
    /**
     * @brief Updates humanoids and moves game entities accordingly.
     * 
     */
    void update();
    /**
     * @brief Displays humanoids and humanoids aliens objects. 
     * 
     * @param window Reference to sf::RenderWindow object.
     */
    void display(sf::RenderWindow& window);
    /**
     * @brief Resets humanoids to their initial state.
     * 
     */
    void resetHumans();

    //Required for sufficient unit testing
    /**
     * @brief Get the Number Captured Humanoids object.
     * 
     * @return int value representing total number of captured humanoids. 
     */
    int getNumberCapturedHumanoids();
    /**
     * @brief Get the Number Of Falling Humanoids object.
     * 
     * @return int value representing total number of falling humanoids. 
     */
    int getNumberOfFallingHumanoids();
    /**
     * @brief Get the Number Of Caught Humanoids object.
     * 
     * @return int value representing total number of caught humanoids. 
     */
    int getNumberOfCaughtHumanoids();
    /**
     * @brief Get the Number Of Tracking Humanoids object.
     * 
     * @return int value representing total number of tracking humanoids. 
     */
    int getNumberOfTrackingHumanoids();
    /**
     * @brief Get the Number Of Tracking Aliens object.
     * 
     * @return int value representing total number of tracking aliens. 
     */
    int getNumberOfTrackingAliens();
    private:
    void moveGameEnitites();
    void moveAliens(std::vector<sf::Sprite>& lander_, float speed);
    float capturespeed_ = -50.0f; 
    float trackingSpeed_ = 100.0f; 
    float fallingspeed_ = 30.0f;    
    humanoidsAliens humanoidsAliens_; 
    catchingHumanoid catchingHumanoid_; 
};

#endif