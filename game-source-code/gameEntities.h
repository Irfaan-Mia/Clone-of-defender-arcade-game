#ifndef GAMEENTITIES_H
#define GAMEENTITIES_H

/**
 * @file gameEntities.h
 * @brief This class is responsible for handling all the events of game entities.
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* Header Files */
#include <SFML/Graphics.hpp>
#include "playerShip.h"
#include "pod.h"
#include "alien.h"
#include "asteroids.h"
#include "score.h"
#include "scrolling.h"
#include "playerShield.h"
#include "handlingHumanoids.h"
#include "playerLives.h"
#include "PlayerProjectiles.h"
#include "fuel.h"
#include <iostream>
#include "displaygameEntities.h"

class gameEntities
{
    public: 
    /**
     * @brief Construct a new game Entities object and initializes certain textures.
     * 
     */
    gameEntities();
    /**
     * @brief Destroy the game Entities object.
     * 
     */
    ~gameEntities();
    /**
     * @brief Sets the delta time required for objects movement.
     * 
     * @param delatTime float value representing change in time.
     */
    void setdt(float delatTime);
    /**
     * @brief Handles user input passes to game objects.
     * 
     * @param event sf::Event representing users keyboard input event.
     */
    void handleInput(sf::Event& event);
    /**
     * @brief Resets game entities to initial state.
     * 
     */
    void reset();
    /**
     * @brief Updates all game entities.
     * 
     */
    void update();
    /**
     * @brief Displays all game entities and views.
     * 
     * @param window Reference to sf::RenderWindow object.
     */
    void display(sf::RenderWindow& window);
    /**
     * @brief Checks if the game has ended.
     * 
     * @return true if the game has ended.
     * @return false if player is still playing.
     */
    bool isGameOver();
    /**
     * @brief Checks if the player has won.
     * 
     * @return true if the player defeated all enemies.
     * @return false if the player is eleminated or all humanoids eliminated. 
     */
    bool gameWon();

    private:
    void updatePlayerShip();
    void updateLanders();
    void updatePods();
    void updateAsteriod();
    void updateHumanoids();

    //GameEntities 
    playerShip playership; 
    alien aliens_; 
    pod pod_; 
    asteroids asteroids_;
    score playerScore_;
    handlingHumanoids human_; 

    //Players shield and lives 
    playerShield playerShield_;
    playerLives playerLives_;  
    PlayerProjectiles playerProjectiles_;
    fuel playerFuel_; 

    //Displaying game entities
    displaygameEntities displayGameEntities_;
    
    //Endgame information
    bool podsDefeated_ = false;
    bool aliensDefeated_ = false;
};

#endif // gameEntities.h