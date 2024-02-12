#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

/** \file screenManager.h
    \brief Contains code for managing different screens in the game.
*/

/* Header Files */
#include <SFML/Graphics.hpp>
#include "splashScreen.h"
#include "preGameScreen.h"
#include "gameScreen.h"
#include "gameoverScreen.h"
#include "scoreScreen.h"
#include "score.h"

class ScreenManager {
public:
    /** \brief Constructor

    Creates a ScreenManager object.
    */
    ScreenManager();

    /** \brief Destructor

     Destroys a ScreenManager object.
    */
    ~ScreenManager();

    /** \brief Updates the current screen

     This function updates the current screen based on the game state and user input.

     \param window Reference to sf::RenderWindow object.
     \param event Reference to sf::Event object.
    */
    void update(sf::RenderWindow& window, sf::Event& event);

    /** \brief Displays the current screen

     This function displays the current screen on the window.

     \param window Reference to sf::RenderWindow object.
    */
    void display(sf::RenderWindow& window);

private:
    enum ScreenState { SPLASH, PREGAME, GAME, GAMEOVER, SCORE}; 
    ScreenState currentState_;
    SplashScreen splashScreen_;
    PreGameScreen preGameScreen_;
    GameScreen gameScreen_;
    ScoreScreen scoreScreen_;

    //End of game screen 
    GameOverScreen gameOverScreen_;
    score playerScore_;

    //Frame rate control
    sf::Clock clock;
};

#endif // SCREENMANAGER_H
