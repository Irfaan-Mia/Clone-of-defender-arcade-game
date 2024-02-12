#ifndef GAMESCREEN_H
#define GAMESCREEN_H

/** \file gameScreen.h
    \brief Presentation layer of the game. Controls gameEntities class. 
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
#include "gameEntities.h"

class GameScreen{
public:

    /** \brief Constructor

        Creates the game screen object

    */
    GameScreen();

    /** \brief Updates game screen

        Updates all game entities within the game screen

    */
    void updateGameEntities();

    /** \brief Returns end game state

        Returns true if the player has won the game by eliminating all enemies

    \return Returns true if player won the game. Otherwise false
    */
    bool gameWon();

    /** \brief Handles keyboard inputs of user

        Checks for a keyboard input and passes it to a function to process the keyboard input 

    \param event sf::Event containing information about event code that occurred
    */
    void handleInput(sf::Event& event);

    /** \brief Display the game screen

        Updates and displays objects within the game screen 

    \param window Specific window that objects update are drawn into
    */
    void display(sf::RenderWindow& window);

    /** \brief Returns state of game 

        Returns the state of the game based on player or enemies conditions

    \return Returns true if game is over. Otherwise false
    */
    bool isGameOver();

    /** \brief Sets delta time

        Sets delta time used by game entities for movement 

    \param deltaTime float value representing Change in time 
    */
    void setdt(float deltaTime);

    /** \brief Resets state of game entities

        Resets game entities to initial state before playing

    */
    void resetState();


private:
    gameEntities gameEntities_;
};

#endif // GAMESCREEN_H