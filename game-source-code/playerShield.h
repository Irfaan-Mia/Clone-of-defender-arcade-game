#ifndef  PLAYERSHIELD_H
#define  PLAYERSHIELD_H

/**
 * @file playerShield.h
 * @brief This class is responsible for activating shield, deactivating shield and displaying players shield icons. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <iostream>

class playerShield
{
    public: 
    /** \brief Constructor.

        Intializes textures required for rendering.

    */
    playerShield(); 

    /**
     * @brief Handles user input. If user presses V will attempt to activate shield.

     * 
     * @param keyPresses sf::Keyboard::Key object containing the specific key pressed by the user. 
     */
    void processInput(sf::Keyboard::Key keyPresses);

    /** \brief Activation of shield.

        Allows manual activation of shield.

    */
    void activateShield();

    /** \brief Updates timer on active shield.

        Checks timer on activated shield and deactivates if max time reached. If no shield is active does nothing. 

    */
    void updateShield();

    /** \brief Allows manual deactivation of shield.

        Allows deactivation of shield if a colllision occurs.

    */
    static void deactivateShield();

    /** \brief Resets shields. 

        Deactivates the shield and sets number of uses to zero.

    */
    void resetShields();

    /** \brief Checks if shield is active.

        Checks if the shield is still active. 

    \return Returns boolean representing true if shield is active. Otherwise false.
    */
    static bool isshieldActive();

    /** \brief Draws shields icons.

        Draws the number of shield uses left as icons.

    \param window Reference to RenderWindow object.
    */
    void drawshieldIcon(sf::RenderWindow& window);

    private:
    static bool shieldActive; 
    static int shieldCount;
    float shieldTimer = 6000.0f; 
    float previousTime;  
    sf::Vector2f playerPos_; 

    sf::Vector2f shieldScale{0.04f,0.04f};
    sf::Vector2f shieldSpacing{200.0f,-10.0f};
    float shieldspacingOffset{30.0f};
    sf::Texture shield_texture; 
};

#endif