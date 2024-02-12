/** \file gameScreen.cpp
*/

/* Header Files */
#include "gameScreen.h"

GameScreen::GameScreen() 
{
}

void GameScreen::updateGameEntities()
{
   gameEntities_.update();
}

bool GameScreen::gameWon()
{
    return gameEntities_.gameWon();
}

void GameScreen::handleInput(sf::Event& event) {
    gameEntities_.handleInput(event);
}

void GameScreen::display(sf::RenderWindow& window) {
   gameEntities_.display(window);
}

bool GameScreen::isGameOver()
{
   return gameEntities_.isGameOver();
}

void GameScreen::setdt(float deltaTime)
{
    gameEntities_.setdt(deltaTime);
}

void GameScreen::resetState()
{
    gameEntities_.reset();
}