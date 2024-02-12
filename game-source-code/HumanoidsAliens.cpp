/** \file humanoidsAliens.cpp
*/

/* Header Files */
#include "HumanoidsAliens.h"

humanoidsAliens::humanoidsAliens()
{
}

humanoidsAliens::~humanoidsAliens()
{
}

void humanoidsAliens::checkalienaboveHumanoid(std::vector<sf::Sprite>& alien_,std::vector<sf::Sprite>& humanoids_)
{
    for(auto i = 0; i < humanoids_.size(); i++)
    {
        for(auto j = 0; j < alien_.size(); j++)
        {
            if(isHumanoidIndexAvailable(i) && checkAlienAboveHumanoidPos(humanoids_[i],alien_[j]))
            {
                TrackingAliens.push_back(alien_[j]);
                trackingHumanoidIndex.push_back(i);
                alien_.erase(alien_.begin() + j);
            }
        }
    }
}

void humanoidsAliens::fixIndices(int index)
{
    decrementIndices(capturedHumanoidIndex,index); 
    decrementIndices(fallingHumanoidsIndex,index);
    decrementIndices(trackingHumanoidIndex,index);
    if(caughtHumanoidIndex >= index)
    {
        caughtHumanoidIndex--; 
    }
}

void humanoidsAliens::decrementIndices(std::vector<int> &indices, int index)
{
    for(auto k = 0; k <indices.size(); k++) 
    {
        if(indices[k] >= index)
        {
            indices[k]--; 
        }
    }
}

bool humanoidsAliens::checkCollision(const sf::FloatRect object1, const sf::FloatRect object2)
{
    if (object1.intersects(object2)) 
    {
        return true; // Collision detected
    }
    return false;
}

bool humanoidsAliens::checkAlienAboveHumanoidPos(sf::Sprite human, sf::Sprite enemy)
{
    if(human.getPosition().x <= enemy.getPosition().x &&
    human.getPosition().x + human.getGlobalBounds().getSize().x/4.0f >= enemy.getPosition().x)
    {
        return true; 
    }
    return false; 
}

void humanoidsAliens::hasAlienCollision(std::vector<sf::Sprite> &alien_, std::vector<sf::Sprite> &humanoids_)
{
    // Iterate through each humanoid
    for (auto humanoidIndex = 0; humanoidIndex < humanoids_.size(); humanoidIndex++)
    {
        // Iterate through each alien sprite
        for (auto alienIndex_ = 0; alienIndex_ < alien_.size(); alienIndex_++)
        {

            // Check if the humanoid collides with the current enemy
            if (checkCollision(humanoids_[humanoidIndex].getGlobalBounds(),alien_[alienIndex_].getGlobalBounds()))
            {
                CapturingAliens.push_back(alien_[alienIndex_]);
                //Setting humanoids position to under the lander
                humanoids_[humanoidIndex].setPosition(alien_[alienIndex_].getGlobalBounds().getSize().x/10.0f + alien_[alienIndex_].getPosition().x,alien_[alienIndex_].getGlobalBounds().getSize().y + alien_[alienIndex_].getPosition().y);
                alien_.erase(alien_.begin() + alienIndex_); 
                trackingHumanoidIndex.erase(trackingHumanoidIndex.begin() + alienIndex_);
                capturedHumanoidIndex.push_back(humanoidIndex);
            }
        }
    }
}

void humanoidsAliens::playerProjectileCollision(std::vector<sf::Sprite>& humanoids_,std::vector<int> &humanoidIndexes, std::vector<projectiles> &playershipProjectiles_, alien &alien_)
{
    for (int i = 0; i < humanoidIndexes.size(); i++) {
        for (int j = 0; j < playershipProjectiles_.size(); j++) {

            if (checkCollision(humanoids_[humanoidIndexes[i]].getGlobalBounds(),playershipProjectiles_[j].getSprite().getGlobalBounds()) && (humanoidIndexes == capturedHumanoidIndex)) { 
                humanoids_.erase(humanoids_.begin() + humanoidIndexes[i]);
                alien_.getEnemySprites().push_back(CapturingAliens[i]);
                CapturingAliens.erase(CapturingAliens.begin() + i);
                //Adjust stored indices to new index values 
                fixIndices(humanoidIndexes[i]);
                humanoidIndexes.erase(humanoidIndexes.begin() + i);
                playershipProjectiles_.erase(playershipProjectiles_.begin() + j); 
                score_.updateScore(EliminationHumanoid);
            }
            else if(checkCollision(CapturingAliens[i].getGlobalBounds(),playershipProjectiles_[j].getSprite().getGlobalBounds()) && (humanoidIndexes == capturedHumanoidIndex)) 
            {
            CapturingAliens.erase(CapturingAliens.begin() + i);
            fallingHumanoidsIndex.push_back(humanoidIndexes[i]);
            humanoidIndexes.erase(humanoidIndexes.begin() + i);
            score_.updateScore(AlienScore);
            }
            else if(checkCollision(playershipProjectiles_[j].getSprite().getGlobalBounds(),humanoids_[humanoidIndexes[i]].getGlobalBounds()) && (fallingHumanoidsIndex == humanoidIndexes))
            {
            humanoids_.erase(humanoids_.begin() + fallingHumanoidsIndex[i]);
            fixIndices(fallingHumanoidsIndex[i]);
            fallingHumanoidsIndex.erase(fallingHumanoidsIndex.begin() + i);
            score_.updateScore(EliminationHumanoid);
            }
        }
    }
}

void humanoidsAliens::checkBorderCollision(std::vector<sf::Sprite> &humanoids_, alien& aliens_)
{
    for(auto i = 0; i < fallingHumanoidsIndex.size(); i++)
    {
        if(humanoids_[fallingHumanoidsIndex[i]].getPosition().y >= 750.0f*0.95)
        {
            humanoids_.erase(humanoids_.begin() + fallingHumanoidsIndex[i]);
            fixIndices(fallingHumanoidsIndex[i]);
            fallingHumanoidsIndex.erase(fallingHumanoidsIndex.begin() + i);
            score_.updateScore(EliminationHumanoid);
        }
    }
    for(auto i = 0; i < CapturingAliens.size();i++)
    {
        if(CapturingAliens[i].getPosition().y <= 0.2f*750.0f)
        {
            aliens_.getEnemySprites().push_back(CapturingAliens[i]);
            CapturingAliens.erase(CapturingAliens.begin() + i);
            humanoids_.erase(humanoids_.begin() + capturedHumanoidIndex[i]); 
            fixIndices(capturedHumanoidIndex[i]);
            capturedHumanoidIndex.erase(capturedHumanoidIndex.begin() + i);
            score_.updateScore(EliminationHumanoid);
        }
    }
}

void humanoidsAliens::checkAlienPlayerShipCollision(playerShip &playership,std::vector<sf::Sprite>& humanoids_,std::vector<sf::Sprite>&HumanoidsALiens_,std::vector<int>&HumanoidsAliensIndex_)
{
    for (auto i = 0; i < HumanoidsALiens_.size(); i++) {
        if (checkCollision(HumanoidsALiens_[i].getGlobalBounds(),playership.getplayerGlobalsBounds())) {
            HumanoidsALiens_.erase(HumanoidsALiens_.begin() + i);
            humanoids_.erase(humanoids_.begin() + HumanoidsAliensIndex_[i]);
            fixIndices(HumanoidsAliensIndex_[i]);
            HumanoidsAliensIndex_.erase(HumanoidsAliensIndex_.begin() + i);
            playerLives playerLives_; 
            playerLives_.eliminatePlayer();
        }
    }
}

void humanoidsAliens::resetHumanoidsAliens()
{
    CapturingAliens.clear(); 
    TrackingAliens.clear(); 
    capturedHumanoidIndex.clear();
   // capturingAlienIndex.clear(); 
    fallingHumanoidsIndex.clear(); 
    trackingHumanoidIndex.clear();
    caughtHumanoidIndex = -1; 
}

bool humanoidsAliens::isHumanoidIndexAvailable(int humanoidIndex)
{
    if(!isIndexAvailable(capturedHumanoidIndex,humanoidIndex) && (caughtHumanoidIndex != humanoidIndex) 
        && !isIndexAvailable(trackingHumanoidIndex,humanoidIndex) && !isIndexAvailable(fallingHumanoidsIndex,humanoidIndex))
    {
        return true;   
    }
    return false; 
}

bool humanoidsAliens::isIndexAvailable(std::vector<int> index, int humanoidIndex)
{
    if(std::find(index.begin(),index.end(),humanoidIndex) != index.end())
    {
        return true; 
    }
    return false;
}

std::vector<sf::Sprite> &humanoidsAliens::getTrackingAliens()
{
    return TrackingAliens;
}

std::vector<sf::Sprite> &humanoidsAliens::getCapturingAliens()
{
    return CapturingAliens;
}

std::vector<int> &humanoidsAliens::getcapturedHumanoidIndex()
{
    return capturedHumanoidIndex;
}

std::vector<int> &humanoidsAliens::getfallingHumanoidsIndex()
{
    return fallingHumanoidsIndex;
}

std::vector<int> &humanoidsAliens::gettrackHumanoidIndex()
{
    return trackingHumanoidIndex;
}

int &humanoidsAliens::getcaughtHumanoidIndex()
{
    return caughtHumanoidIndex;
}
