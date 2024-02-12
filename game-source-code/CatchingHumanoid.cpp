#include "CatchingHumanoid.h"

catchingHumanoid::catchingHumanoid()
{
}

catchingHumanoid::~catchingHumanoid()
{
}

void catchingHumanoid::checkHumanoidCaught(sf::FloatRect playerPos,std::vector<sf::Sprite>&humanoids_,std::vector<int>&fallingHumanoidsIndex,int&caughtHumanoidIndex)
{
    for(int i = 0; i < fallingHumanoidsIndex.size(); i++)
    {
        sf::FloatRect humanoidsBounds = humanoids_[fallingHumanoidsIndex[i]].getGlobalBounds();
        sf::FloatRect playershipBounds = playerPos;
            if (playershipBounds.intersects(humanoidsBounds) && caughtHumanoidIndex == -1) {
                caughtHumanoidIndex = fallingHumanoidsIndex[i];
                fallingHumanoidsIndex.erase(fallingHumanoidsIndex.begin() + i);
                return;
            }
    }
}

void catchingHumanoid::moveHumanoidwithPlayer(std::vector<sf::Sprite> &humanoids_, int &caughtHumanoidIndex)
{
    if(caughtHumanoidIndex != -1)
    {
        humanoids_[caughtHumanoidIndex].setPosition(playerPos_);
    }
}

void catchingHumanoid::checkHumanoidSafe(std::vector<sf::Sprite> &humanoids_, int &caughtHumanoidIndex)
{
    if(caughtHumanoidIndex != -1)
    {
    if(humanoids_[caughtHumanoidIndex].getPosition().y >= 750.0f*0.92f)
    {
        caughtHumanoidIndex = -1;
    }
    }
}

void catchingHumanoid::setplayerPos(sf::Vector2f playerPos)
{
    playerPos_ = playerPos;
}
