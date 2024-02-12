/** \file human.cpp
*/

/* Header Files */
#include "human.h"

human::human()
{
    previousTime_ = clock(); 
    if (!humanoidTexture_.loadFromFile("resources/humanoid.png")) 
    { 
        std::cerr << "ERROR::LOADING HUMANOID TEXTURE" << std::endl;
        return;
    }
}

human::~human()
{
}

void human::setDeltaTme(float deltaTme)
{
    dt_ = deltaTme; 
}

void human::addHumanoid(sf::Sprite humanoid_)
{
    humanoids_.push_back(humanoid_);
}

std::vector<sf::Vector2f> human::humanoidsPositions()
{
    std::vector<sf::Vector2f> humanoidsPositions; 
    for(auto& human: humanoids_)
    {
        humanoidsPositions.push_back(human.getPosition());
    }
    return humanoidsPositions;
}

void human::resetHumanoids()
{
    previousTime_ = clock();
    humanoids_.clear();
    humanoidCounter_ = 0;
}

void human::updateHumanoids()
{
    spawnHumanoid();
}

void human::createHumanoid()
{
    sf::Sprite humanoidSprite_;
    humanoidSprite_.setTexture(humanoidTexture_);
    humanoidSprite_.setScale(humanoidScale_);
    auto bottomBorder_ = windowSize_.y * 0.92; // Bottom boundary of the bottom 20% of the screen

    // Randomize enemy position in the bottom 20% of the screen
    auto collisionDetected = true;
    while (collisionDetected) {
        auto randX_ = static_cast<float>(std::rand() % (3000 - 100)); // Adjusted X range
        humanoidSprite_.setPosition(randX_, bottomBorder_);
        collisionDetected = checkCollision(humanoidSprite_, humanoids_);
    }
    addHumanoid(humanoidSprite_);
}

void human::spawnHumanoid()
{
    if ((clock() - previousTime_ >= spawnInterval_) and humanoidCounter_ < totalHumanoids_)
    {
        createHumanoid();
        humanoidCounter_++;
        previousTime_ = clock();
    }
}

void human::displayGameEntities(std::vector<sf::Sprite> &entities, sf::RenderWindow &window)
{
    if (!entities.empty()) {
        for (auto& entitie : entities) {
            window.draw(entitie);
        }
    }
}


bool human::checkCollision(const sf::Sprite& newHumanoid_, const std::vector<sf::Sprite>& existingHumanoids_) 
{
    for (const auto& existingHumanoid_ : existingHumanoids_) 
    {
        sf::FloatRect newHumanoid_bounds = newHumanoid_.getGlobalBounds();
        sf::FloatRect existingHumanoid_bounds = existingHumanoid_.getGlobalBounds();
            if (newHumanoid_bounds.intersects(existingHumanoid_bounds)) 
            {
                return true; // Collision detected
            }
    }

    return false; // Else no collision detected
}

void human::moveHumanoid(std::vector<int> &index, float speed)
{
    for(auto i = 0; i < index.size(); i++)
    {
        humanoids_[index[i]].move(0.0f,speed*dt_);
        // if(humanoids_[index[i]].getPosition().y > windowSize_.y*0.95)
        // {
        //     humanoids_.erase(humanoids_.begin() + index[i]);
        //     fixIndices(index[i]);
        // }
    }
}

std::vector<sf::Sprite> &human::getHumanoids()
{
    return humanoids_;
}

bool human::checkHumanoidCounter()
{
    if(humanoidCounter_ == totalHumanoids_)
    {
        return true;
    }
    return false;
}
