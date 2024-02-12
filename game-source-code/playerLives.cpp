/** \file playerLives.cpp
*/

/* Header Files */
#include "playerLives.h"

int playerLives::remainingLives = 3;

playerLives::playerLives()
{
    if(!playerLifeTexture.loadFromFile("resources/ship_right.png"))
    {
        std::cerr << "ERROR::LOADING SHIP_RIGHT TEXTURE" << std::endl;
        return;
    }
     
    //Player lives 
    playerLife.setTexture(playerLifeTexture);
    playerLife.setScale(playerlifeScale);
}

int playerLives::getplayerLives()
{
    return remainingLives;
}

void playerLives::decreaseplayerLives()
{
    if(playerShield::isshieldActive())
    {
        playerShield::deactivateShield();
    }
    else
    {
        remainingLives--;
    }
}

void playerLives::eliminatePlayer()
{
    if(playerShield::isshieldActive())
    {
        playerShield::deactivateShield();
    }
    else
    {
    remainingLives = 0;
    }
}

bool playerLives::isPlayerEliminated()
{
    return remainingLives == 0;
}

void playerLives::resetplayerLives()
{
    remainingLives = 3; 
}

void playerLives::displayLives(sf::RenderWindow &window)
{
    for(auto i = 0; i < remainingLives; i++)
    {
        playerLife.setPosition(0.0f + i*playerlifeSpacing.x, playerlifeSpacing.y); 
        window.draw(playerLife); 
    }
}
