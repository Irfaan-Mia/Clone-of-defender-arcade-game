/** \file PlayerProjectiles.cpp
*/

/* Header Files */
#include "PlayerProjectiles.h"

PlayerProjectiles::PlayerProjectiles()
{
    if(!projectile_texture.loadFromFile("resources/shoot.png"))
    {
        std::cerr << "ERROR::LOADING PROJECTILE TEXTURE" << std::endl;
        return;  
    }
    if(!gun_shot_buffer.loadFromFile("resources/projectile.wav"))
    {
        std::cerr << "ERROR::LOADING PROJECTILE SOUND" << std::endl;
        return;
    }
    previousTime_ = clock();
    gun_shot.setBuffer(gun_shot_buffer);
    gun_shot.setVolume(10);
}

PlayerProjectiles::~PlayerProjectiles()
{
}

void PlayerProjectiles::processEvent(sf::Vector2f direction, sf::Vector2f PlayerPos, sf::Keyboard::Key keyPressed)
{
    if(clock() - previousTime_ > 100.0f)
    {
        shootbullet(direction, PlayerPos, keyPressed);
        previousTime_ = clock();
    }
}

void PlayerProjectiles::shootbullet(sf::Vector2f direction, sf::Vector2f PlayerPos, sf::Keyboard::Key keyPressed)
{
    if(keyPressed == sf::Keyboard::Space)
    {
        sf::Vector2f gun = PlayerPos; 
        gun.y += 25.0f; 
        gun_shot.play();
        playerProjectiles_.push_back(projectiles(projectile_texture, direction,bulletspeed_,gun));
    }
}

void PlayerProjectiles::update()
{
    for(auto& bullet: playerProjectiles_)
    {
        bullet.update();
    }
    checkProjectileCollisionBorder(line1,line2);
}

void PlayerProjectiles::setdt(float deltaTime)
{
    for(auto& bullet:playerProjectiles_)
    {
        bullet.setdt(deltaTime); 
    }
}

void PlayerProjectiles::setprojectileBorder(sf::RectangleShape &LeftBorder_, sf::RectangleShape &RightBorder_)
{
    line1 = LeftBorder_; 
    line2 = RightBorder_;
}

void PlayerProjectiles::resetProjectiles()
{
    playerProjectiles_.clear();
    previousTime_ = clock();
}

std::vector<projectiles> &PlayerProjectiles::getPlayerProjectiles()
{
    return playerProjectiles_; 
}

void PlayerProjectiles::display(sf::RenderWindow &window)
{
    for(auto& bullet: playerProjectiles_)
    {
        wrapProjectile(bullet);
        bullet.drawto(window);
    }
}

int PlayerProjectiles::numberProjectiles()
{
    return playerProjectiles_.size();
}

void PlayerProjectiles::checkProjectileCollisionBorder(sf::RectangleShape &LeftBorder_, sf::RectangleShape &RightBorder_)
{
    for(auto i = 0; i < playerProjectiles_.size();i++)
    {
        if(LeftBorder_.getPosition().x > maxgameView_ - 1350.0f/2.0f)
        {
            if(playerProjectiles_[i].get_projectile_position().x > RightBorder_.getPosition().x && playerProjectiles_[i].get_projectile_position().x < LeftBorder_.getPosition().x )
            {
            playerProjectiles_.erase(playerProjectiles_.begin() + i);
            }
        }
        else if(RightBorder_.getPosition().x < 1350.0f/2.0f)
        {
            if(playerProjectiles_[i].get_projectile_position().x > RightBorder_.getPosition().x && playerProjectiles_[i].get_projectile_position().x < LeftBorder_.getPosition().x )
            {
            playerProjectiles_.erase(playerProjectiles_.begin() + i);
            }
        }
        else if(playerProjectiles_[i].get_projectile_position().x < LeftBorder_.getPosition().x || playerProjectiles_[i].get_projectile_position().x > RightBorder_.getPosition().x)
        {
            playerProjectiles_.erase(playerProjectiles_.begin() + i);
        }
    }
}

void PlayerProjectiles::wrapProjectile(projectiles &bullet)
{
    if(bullet.get_projectile_position().x < 0.0f)
    {
        bullet.getSprite().setPosition(3000.0f,bullet.getSprite().getPosition().y);
        }
        else if(bullet.get_projectile_position().x > 3000.0f)
        {
            bullet.getSprite().setPosition(0.0f,bullet.getSprite().getPosition().y);
        } 
}
