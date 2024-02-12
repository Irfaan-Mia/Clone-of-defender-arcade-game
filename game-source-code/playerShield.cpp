/** \file playerShield.cpp
*/

/* Header Files */
#include "playerShield.h"

bool playerShield::shieldActive = false; 
int playerShield::shieldCount = 3; 

playerShield::playerShield()
{ 
    if(!shield_texture.loadFromFile("resources/shield.png"))
    {
        std::cerr << "ERROR LOADING playershield.png" << std::endl;
        return; 
    }
}

void playerShield::processInput(sf::Keyboard::Key keyPresses)
{
    if(!shieldActive) 
    {
        if(keyPresses == sf::Keyboard::Key::V)
        {
            activateShield();
        }
    }
}

void playerShield::activateShield()
{
    if(shieldCount > 0)
    {
    shieldActive = true; 
    shieldCount--; 
    }
}

void playerShield::updateShield()
{
    if(shieldActive) 
    {
        if(clock() - previousTime >= shieldTimer && shieldCount > 0)
        {
            deactivateShield(); 
        }
    }
    else
    {
        previousTime = clock();
    }
}

void playerShield::deactivateShield()
{
    shieldActive = false; 
}

void playerShield::resetShields()
{
    shieldActive = false; 
    shieldCount = 3; 
}

bool playerShield::isshieldActive()
{
    if(shieldActive) 
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

void playerShield::drawshieldIcon(sf::RenderWindow& window)
{
    sf::Sprite shield; 
    shield.setTexture(shield_texture);
    shield.setScale(shieldScale);
    //Draw icons of shield 
    for(auto i = 0; i < shieldCount; i++)
    {
    shield.setPosition(shieldSpacing.x + i*shieldspacingOffset,shieldSpacing.y);
    window.draw(shield);
    }
}
