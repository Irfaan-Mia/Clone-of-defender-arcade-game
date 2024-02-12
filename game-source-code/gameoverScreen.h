#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

/** \file gameoverScreen.h
    \brief Contains code for managing game over screen for when the players has lost or won.
*/

/* Header Files */
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include "score.h"

class GameOverScreen
{
    public:
    /** \brief Constructor

    Creates a GamOverScreen object and initializes private variables
    */
    GameOverScreen();

    /** \brief Destructor

     Destroys a GameOverScreen object.
    */
    ~GameOverScreen();

    /** \brief Displays the game over screen 

     Displays the game over screen when player lost allowing for the player to exit or restart game

     \param window Reference to sf::RenderWindow object.
    */
    void display(sf::RenderWindow& window, bool &isWinner_, int score_);

    private: 
    int playerScore_ = 0;
    sf::Texture background_image; 
    sf::Font font; 
    sf::Text GameOverText;
    sf::Text winnerText_;
    sf::Text loserText_;
    sf::Text scoreText_;
    sf::Text RestartText;
};

#endif // GAMEOVERSCREEN_H