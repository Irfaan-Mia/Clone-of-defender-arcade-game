/** \file screenManager.cpp
*/

/* Header Files */
#include "screenManager.h"
#include <iostream> 

ScreenManager::ScreenManager(){
    // Set the initial state of the screen to the splash screen
    currentState_ = SPLASH;
}

ScreenManager::~ScreenManager() {}

void ScreenManager::update(sf::RenderWindow& window, sf::Event& event) {
    // Switch statement based on the current state of the screen
    switch (currentState_) {
        case SPLASH:
            // Switch the screen to the pre game screen  if 'SPC' is presssed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                currentState_ = PREGAME;
                gameScreen_.resetState();
            } else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::H)) {
                currentState_ = SCORE;
                gameScreen_.resetState();
            }
            break;
        case PREGAME:
            // Switch the screen to the GAME screen  if 'SPC' is presssed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) {
                currentState_ = GAME;
                gameScreen_.resetState();
            break;
        case GAME:{
            float dt = clock.restart().asSeconds();
            gameScreen_.handleInput(event);
            gameScreen_.setdt(dt);
            gameScreen_.updateGameEntities();
            if(gameScreen_.isGameOver()) //Temporary to test game over screen
            {
                playerScore_.updateHighScore();
                currentState_ = GAMEOVER;
                window.setView(window.getDefaultView());
            }
            // TODO
            break;
        }
        case GAMEOVER:
            // playerScore_.saveHighScores();
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) //Temporary to test game over screen
            {
                currentState_ = SPLASH;
                gameScreen_.resetState();
            }
            break;
        case SCORE:
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)) //Temporary to test game over screen
            {
                currentState_ = SPLASH;
                gameScreen_.resetState();
            }
            break;
        default:
            break;
    }
    }
}

void ScreenManager::display(sf::RenderWindow& window) {
    // Switch statement based on the current state of the screen
    auto gameWon_ = false;
    switch (currentState_) {
        case SPLASH:
            // Display the splash screen
            clock.restart();
            splashScreen_.display(window);
            break;
        case PREGAME:
            // Display the pre game screen
            clock.restart();
            preGameScreen_.display(window);
            break;
        case GAME:{
            // Display the game screen
            gameScreen_.display(window);
            break;
        }
        case GAMEOVER:
            clock.restart();
            gameWon_ = gameScreen_.gameWon();
            gameOverScreen_.display(window, gameWon_, playerScore_.getScore());
            break;
        case SCORE:
            clock.restart();
            scoreScreen_.display(window);
            break;
        default:
            break;
    }
}
