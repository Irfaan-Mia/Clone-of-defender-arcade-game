/** \file gameEntities.cpp
*/

/* Header Files */
#include "gameEntities.h"

gameEntities::gameEntities()
{
    // if(!background_texture_.loadFromFile("resources/ground.png"))
    // {
    //     return; 
    // }
    // background_texture_.setRepeated(true);
    // background_sprite_.setTexture(background_texture_);
    // background_sprite_.setPosition(0.0f,100.0f);
    // background_sprite_.setScale(3000.0f/1350.0f,750.0f/1110.0f);
}

gameEntities::~gameEntities()
{
}

void gameEntities::setdt(float delatTime)
{
    //Update dt values 
    playership.setdt(delatTime);
    playerProjectiles_.setdt(delatTime);
    pod_.setDeltaTime(delatTime);
    aliens_.setDeltaTime(delatTime);
    asteroids_.setDeltaTime(delatTime);
    human_.setDeltaTme(delatTime);
}

void gameEntities::handleInput(sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed) {
        // Send information to change player's position
        playership.processEvent(event.key.code, true);
        // Send information to shoot players projectiles
        playerProjectiles_.processEvent(playership.getPlayerDirection(),playership.getPos(),event.key.code);
        // Send information to activate the players shield 
        playerShield_.processInput(event.key.code); 
    } else if (event.type == sf::Event::KeyReleased) {
        // Handle key release events
        playership.processEvent(event.key.code, false);
    }
}

void gameEntities::reset()
{
    aliensDefeated_ = false; 
    podsDefeated_ = false; 
    playerProjectiles_.resetProjectiles();
    playerShield_.resetShields();
    playerLives_.resetplayerLives();
    playership.resetPlayerShip();
    aliens_.resetAliens();
    aliens_.resetSpawnTimer();
    pod_.resetPods();
    pod_.resetSpawnTimer();
    asteroids_.resetAsteroids();
    human_.resetHumans();
}

void gameEntities::update()
{
    updatePlayerShip();
    updatePods();
    updateLanders();
    updateAsteriod();
    updateHumanoids();
}

void gameEntities::display(sf::RenderWindow &window)
{
    displayGameEntities_.display(window, playership, aliens_, pod_, asteroids_,playerScore_, human_, playerShield_,playerLives_,playerProjectiles_,playerFuel_);
}

bool gameEntities::isGameOver()
{
    if(playerLives_.isPlayerEliminated() or gameWon() or human_.checkallhumansEliminated() or playership.isGameOver())
    {
        return true; 
    }
    return false; 
}

bool gameEntities::gameWon()
{
    if (podsDefeated_ and aliensDefeated_ and human_.checkenemiesDeafeated())
    {
        return true;
    } else return false;
}

void gameEntities::updatePlayerShip()
{
    //Update player ship
    playership.update();
    playerProjectiles_.update();
    playerShield_.updateShield();
    playerProjectiles_.setprojectileBorder(displayGameEntities_.getborder()[0],displayGameEntities_.getborder()[1]);
    playerFuel_.checkcollisionwithFuel(playership.getplayerGlobalsBounds());
    playerFuel_.spawnFuel();
    playerFuel_.updatefuelGauge();
}

void gameEntities::updateLanders()
{
    //Update Lander Enemy
    aliens_.setPlayersPosition(playership.getPos());
    aliens_.checkProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    aliens_.checkMissilesCollision(playership);
    aliens_.checkPlayerCollision(playership);
    aliens_.shootbullets();
    aliens_.updateEnemies();
    aliensDefeated_ = aliens_.defeatedEnemies();
}

void gameEntities::updatePods()
{
    //Update Pods 
    pod_.setPlayersPosition(playership.getPos());
    pod_.checkProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    pod_.checkSwarmProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    pod_.checkPlayerCollision(playership); 
    pod_.checkSwarmCollision(playership);
    pod_.updatePods();
    podsDefeated_ = pod_.defeatedEnemies();
}

void gameEntities::updateAsteriod()
{
    //Update asteroids
    asteroids_.setPlayersPosition(playership.getPos());
    asteroids_.checkProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    asteroids_.checkPlayerCollision(playership);
    asteroids_.updateEnemies();
}

void gameEntities::updateHumanoids()
{  
    //Update humanoids 
    human_.checkCollisions(aliens_,playerProjectiles_.getPlayerProjectiles(),playership);
    human_.update();
}

