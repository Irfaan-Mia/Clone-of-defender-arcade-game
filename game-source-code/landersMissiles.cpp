#include "landersMissiles.h"


landersMissiles::landersMissiles()
{
    if(!bullet_texture.loadFromFile("resources/arrow.png"))
    {
        std::cerr << "ERROR LOADING arrow.png" << std::endl;
        return; 
    }
}

landersMissiles::~landersMissiles()
{
}

void landersMissiles::addlanderMissile(sf::Vector2f landersPosition, sf::Vector2f playersPosition)
{
    //Centre closer to center of player ships position 
    double tempAngle = atan2((playersPosition.y+ 20.0f) - landersPosition.y, (playersPosition.x + 30.0f) - landersPosition.x);
    landersMissiles_.push_back(projectiles(bullet_texture,{static_cast<float>(cos(tempAngle)),static_cast<float>(sin(tempAngle))},movementSpeed_,landersPosition));
}

std::vector<projectiles>& landersMissiles::getbullets()
{
    return landersMissiles_;
}

void landersMissiles::moveBullets()
{
    auto height_ = 900.0f; 
    auto topBorder_ = height_ * 0.17;
    auto width_ = 3000.0f;

    //Each bullet made will have corresponding angle so same size
    for(auto i = 0; i < landersMissiles_.size(); i++)
    {
        landersMissiles_[i].update();
        if(landersMissiles_[i].getSprite().getPosition().x < playersPosition_.x - 1350.0f/2.0f || 
        landersMissiles_[i].getSprite().getPosition().x > playersPosition_.x + 1350.0f/2.0f || 
        landersMissiles_[i].getSprite().getPosition().y <= topBorder_ || 
        landersMissiles_[i].getSprite().getPosition().y > height_)
        {
            landersMissiles_.erase(landersMissiles_.begin() + i);
        }
    }
}

void landersMissiles::removeBullet(const int& index)
{
    landersMissiles_.erase(landersMissiles_.begin() + index);
}

void landersMissiles::draw(sf::RenderWindow &window)
{
    for(auto& missile: landersMissiles_)
    {
        missile.drawto(window);
    }
}

void landersMissiles::resetLandersMissiles()
{
    landersMissiles_.clear();
}

void landersMissiles::setplayerPosition(sf::Vector2f Position_)
{
    playersPosition_ = Position_;
}

void landersMissiles::setdt(float deltaTime)
{
    for(auto& missile: landersMissiles_)
    {
        missile.setdt(deltaTime);
    }
}
