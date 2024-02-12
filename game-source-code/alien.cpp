/** \file alien.cpp
*/

/* Header Files */
#include "alien.h"

alien::alien()
{
    if (!enemyTexture_.loadFromFile("resources/enemy-lander.png")) 
    {
        std::cerr << "ERROR::LOADING pod texture" << std::endl;
        return;
    }
    
    if (!collisionSoundBuffer_.loadFromFile("resources/ship-collision.wav")) 
    {
        std::cerr << "ERROR::LOADING SHIP COLLISION SOUND" << std::endl;
        return;
    }

    collisionSound_.setBuffer(collisionSoundBuffer_);
    collisionSound_.setVolume(10);

    enemy::enemySpeed_ = enemySpeed_; 
    enemy::maxEnemies_ = totalEnemies_; 
    enemy::enemyspawnInterval_ = spawnInterval_; 
    enemy::enemyScale_ = {1.0f,1.0f};
}

alien::~alien()
{
}

const std::vector<projectiles> &alien::getLandersMissiles()
{
    return landersBullets_.getbullets();
}

void alien::resetAliens()
{
    enemies_.clear();    
    landersBullets_.resetLandersMissiles();
    enemy::enemyCounter_ = 0; 
}

void alien::resetSpawnTimer()
{
    previousTime_ = clock();
}

void alien::removeLandersMissile(const int& index_)
{
    landersBullets_.removeBullet(index_);
}

bool alien::hasProjectileCollision(std::vector<projectiles> &playershipProjectiles_) {
    landersBullets_.setplayerPosition(enemy::playerPosition_);
    for (int i = 0; i < enemies_.size(); i++) {
        for (int j = 0; j < playershipProjectiles_.size(); j++) {
            sf::FloatRect alienBounds_ = enemies_[i].getGlobalBounds();
            sf::FloatRect projectilesBounds_ = playershipProjectiles_[j].getSprite().getGlobalBounds();
            if (alienBounds_.intersects(projectilesBounds_)) {
                return true;
            }
        }
    }
    return false;
}

void alien::checkProjectileCollision(std::vector<projectiles> &playershipProjectiles_)
{
    // Check for collision
    if (hasProjectileCollision(playershipProjectiles_)) 
    {
        collisionSound_.play();

        // Handle collision actions
        for (int i = 0; i < enemies_.size(); i++) 
        {
            for (int j = 0; j < playershipProjectiles_.size(); j++) 
            {
                sf::FloatRect alienBounds_ = enemies_[i].getGlobalBounds();
                sf::FloatRect projectilesBounds_ = playershipProjectiles_[j].getSprite().getGlobalBounds();
                if (alienBounds_.intersects(projectilesBounds_)) 
                {
                    enemies_.erase(enemies_.begin() + i);
                    playershipProjectiles_.erase(playershipProjectiles_.begin() + j);
                    playerScore_.updateScore(alienPoints_);
                }
            }
        }
    }
}

bool alien::hasMissilesCollision(playerShip& playerShip_) {
    // Iterate through the lander's missiles and check for collisions
    std::vector<projectiles>& alienMissiles_ = landersBullets_.getbullets();
    for (projectiles& alienMissile_ : alienMissiles_) {
        sf::FloatRect playersBounds_ = playerShip_.getplayerGlobalsBounds();
        sf::FloatRect alienMissileBounds_ = alienMissile_.getSprite().getGlobalBounds();

        // Check for collision between player's ship and lander missile
        if (playersBounds_.intersects(alienMissileBounds_)) {
            return true;
        }
    }
    return false;
}

void alien::checkMissilesCollision(playerShip &playerShip_)
{
    // Check for collision 
    if (hasMissilesCollision(playerShip_)) 
    {
        collisionSound_.play();

        // Handle collision actions
        std::vector<projectiles>& alienMissiles_ = landersBullets_.getbullets();
        auto counter_ = 0;
        for (auto& alienMissile_ : alienMissiles_) 
        {
            sf::FloatRect playersBounds_ = playerShip_.getplayerGlobalsBounds();
            sf::FloatRect alienMissileBounds_ = alienMissile_.getSprite().getGlobalBounds();

            // Check for collision between player's ship and lander missile
            if (playersBounds_.intersects(alienMissileBounds_)) 
            {
                removeLandersMissile(counter_);
                playerLives playerLives_; 
                playerLives_.decreaseplayerLives();
            }
            counter_++;
        }
    }
}


void alien::shootbullets()
{
    if (!enemies_.empty())
    {
        static clock_t spawnTimer_ = clock();
        auto currentTime_ = clock();
        auto elapsedTime_ = static_cast<double>(currentTime_ - spawnTimer_) / CLOCKS_PER_SEC * 1000;
        auto spawnInterval_ = 5000;

        landersBullets_.setdt(dt_);

        //Control rate of fire for landers
        if (elapsedTime_ >= shootingInterval_)
        {
            for (auto& lander_ : enemies_)
            {
                addBullet(lander_);
            }

            spawnTimer_ = currentTime_;
        }
    }
    landersBullets_.moveBullets();
}

void alien::addBullet(sf::Sprite enemy_)
{
    landersBullets_.addlanderMissile(enemy_.getPosition(),playerPosition_);
}

void alien::display(sf::RenderWindow &window_)
{
    // Display Aliens (Landers)
    if (!enemy::enemies_.empty()) {
        for (auto& currentAlien_ : enemy::enemies_) {
            window_.draw(currentAlien_);
        }
    }

    landersBullets_.draw(window_);
}