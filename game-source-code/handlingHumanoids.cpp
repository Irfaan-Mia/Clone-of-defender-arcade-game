/** \file handlingHumanoids.cpp
*/

/* Header Files */
#include "handlingHumanoids.h"

handlingHumanoids::handlingHumanoids()
{
}

handlingHumanoids::~handlingHumanoids()
{
}

void handlingHumanoids::checkCollisions(alien & alien_,std::vector<projectiles> &playershipProjectiles_,playerShip& playership)
{
    //Checking collisions between humanoids and aliens 
    humanoidsAliens_.checkalienaboveHumanoid(alien_.getEnemySprites(),human::getHumanoids());
    humanoidsAliens_.hasAlienCollision(humanoidsAliens_.getTrackingAliens(),human::getHumanoids());
    humanoidsAliens_.playerProjectileCollision(human::getHumanoids(),humanoidsAliens_.getcapturedHumanoidIndex(),playershipProjectiles_,alien_);
    humanoidsAliens_.playerProjectileCollision(human::getHumanoids(),humanoidsAliens_.getfallingHumanoidsIndex(),playershipProjectiles_,alien_);
    humanoidsAliens_.checkBorderCollision(human::getHumanoids(),alien_);
    //Checking collisions for caught humanoids 
    catchingHumanoid_.setplayerPos(playership.getPos());
    catchingHumanoid_.checkHumanoidCaught(playership.getplayerGlobalsBounds(),human::getHumanoids(),humanoidsAliens_.getfallingHumanoidsIndex(),humanoidsAliens_.getcaughtHumanoidIndex());
    catchingHumanoid_.checkHumanoidSafe(human::getHumanoids(),humanoidsAliens_.getcaughtHumanoidIndex());
    //Checking player ship and captured humanoids and aliens collisions
    humanoidsAliens_.checkAlienPlayerShipCollision(playership,human::getHumanoids(),humanoidsAliens_.getCapturingAliens(),humanoidsAliens_.getcapturedHumanoidIndex());
    humanoidsAliens_.checkAlienPlayerShipCollision(playership,human::getHumanoids(),humanoidsAliens_.getTrackingAliens(),humanoidsAliens_.gettrackHumanoidIndex());

}

bool handlingHumanoids::checkenemiesDeafeated()
{
    if((humanoidsAliens_.getCapturingAliens().size() == 0) && (humanoidsAliens_.getTrackingAliens().size() == 0) && (human::getHumanoids().size() != 0))
    {
        return true;
    }
    return false;
}

bool handlingHumanoids::checkallhumansEliminated()
{
    if(human::getHumanoids().size() == 0 && human::checkHumanoidCounter())
    {
        return true; 
    }
    return false;
}

void handlingHumanoids::update()
{
    human::updateHumanoids();
    moveGameEnitites();
}

void handlingHumanoids::display(sf::RenderWindow &window)
{
    human::displayGameEntities(human::getHumanoids(),window);
    human::displayGameEntities(humanoidsAliens_.getTrackingAliens(),window);
    human::displayGameEntities(humanoidsAliens_.getCapturingAliens(),window);
}

void handlingHumanoids::moveGameEnitites()
{
    moveAliens(humanoidsAliens_.getTrackingAliens(),trackingSpeed_);
    moveAliens(humanoidsAliens_.getCapturingAliens(),capturespeed_);
    human::moveHumanoid(humanoidsAliens_.getcapturedHumanoidIndex(),capturespeed_);
    human::moveHumanoid(humanoidsAliens_.getfallingHumanoidsIndex(),fallingspeed_);
    catchingHumanoid_.moveHumanoidwithPlayer(human::getHumanoids(),humanoidsAliens_.getcaughtHumanoidIndex());
}


void handlingHumanoids::moveAliens(std::vector<sf::Sprite> &lander_, float speed)
{
    for(auto& lander: lander_)
    {
        lander.move(0.0f,speed*dt_);
    }
}

void handlingHumanoids::resetHumans()
{
    human::resetHumanoids();
    humanoidsAliens_.resetHumanoidsAliens();
}

int handlingHumanoids::getNumberCapturedHumanoids()
{
    return humanoidsAliens_.getcapturedHumanoidIndex().size();
}

int handlingHumanoids::getNumberOfFallingHumanoids()
{
    return humanoidsAliens_.getfallingHumanoidsIndex().size();
}

int handlingHumanoids::getNumberOfCaughtHumanoids()
{
    return humanoidsAliens_.getcaughtHumanoidIndex();
}

int handlingHumanoids::getNumberOfTrackingHumanoids()
{
    return humanoidsAliens_.gettrackHumanoidIndex().size();
}

int handlingHumanoids::getNumberOfTrackingAliens()
{
    return humanoidsAliens_.getTrackingAliens().size();
}
