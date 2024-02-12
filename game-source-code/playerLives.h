#ifndef PLAYERLIVES_H
#define PLAYERLIVES_H

/**
 * @file playerLives.h
 * @brief This class is responsible for displaying, decreasing player lives and eliminating the player causing game to end.  
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "playerShield.h"

class playerLives
{
    public: 
    /**
     * @brief Construct a new player Lives object.
     * 
     */
    playerLives();
    /** \brief Returns current players lives.

        Returns the current total number of players lives.
    \return integer value of remaining number of players lives.
    */
    int getplayerLives();
    /** \brief Decrements players lives by one.

        Decreases the current number of lives of the player by one.

    */
    void decreaseplayerLives();
    /**
     * @brief Sets player lives to zero.
     * 
     */
    void eliminatePlayer();
    /**
     * @brief Checks if player still has lives.
     * 
     * @return true if the player has no lives.
     * @return false if the player still has lives.
     */
    bool isPlayerEliminated();
    /**
     * @brief Resets player lives to maximum number of player lives.
     * 
     */
    void resetplayerLives();
    /** \brief Displays players lives.

        Displays the corresponding number of lives of the player.
    
    \param window Reference to sf::RenderWindow object.
    */
    void displayLives(sf::RenderWindow& window);

    private: 
    sf::Sprite playerLife;
    sf::Texture playerLifeTexture;
    sf::Vector2f playerlifeScale{0.7f,0.7f};
    sf::Vector2f playerlifeSpacing{50.0f,5.0f}; 
    int maxPlayerLives = 3; 
    static int remainingLives; 
};

#endif