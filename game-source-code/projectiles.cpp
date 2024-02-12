/** \file projectiles.cpp
*/

/* Header Files */
#include "projectiles.h"
#include <iostream>

projectiles::projectiles(sf::Texture& projectiles_texture,sf::Vector2f direction,float movementspeed,sf::Vector2f starting_pos)
{
    projectile_shape_.setTexture(projectiles_texture);
    projectile_shape_.setPosition(starting_pos);
    projectile_shape_.setScale(projectile_scale);
    direction_ = direction;
    movementspeed_ = movementspeed;
}

projectiles::~projectiles()
{
}

void projectiles::update()
{
    projectile_shape_.move(direction_.x*movementspeed_*dt_,direction_.y*movementspeed_*dt_);
}

void projectiles::drawto(sf::RenderTarget& window)
{
    window.draw(projectile_shape_);
}

sf::Sprite &projectiles::getSprite()
{
    // TODO: insert return statement here
    return projectile_shape_; 
}

sf::Vector2f projectiles::get_projectile_position()
{
    return projectile_shape_.getPosition();
}

void projectiles::setdt(float deltaTime)
{
    dt_ = deltaTime;
}
