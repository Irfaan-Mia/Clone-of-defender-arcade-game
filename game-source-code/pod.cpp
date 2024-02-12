/** \file pod.cpp
*/

/* Header Files */
#include "pod.h"


pod::pod()
{
    if (!enemyTexture_.loadFromFile("resources/enemy-pod.png")) 
    { 
        std::cerr << "ERROR::LOADING pod texture" << std::endl;
        return;
    }
    if (!swarmTexture_.loadFromFile("resources/enemy-swarmer.png")) 
    { 
        std::cerr << "ERROR::LOADING swarm texture" << std::endl;
        return;
    }
    if (!collisionSoundBuffer_.loadFromFile("resources/ship-collision.wav"))
    {
        std::cerr << "ERROR::LOADING SHIP COLLISION SOUND" << std::endl;
        return;
    }
    if (!swarmSoundBuffer_.loadFromFile("resources/swarm-sound.wav")) 
    {
        std::cerr << "ERROR::LOADING SWARM SOUND" << std::endl;
        return;
    }
    
    swarmSprite_.setTexture(swarmTexture_);
    collisionSound_.setBuffer(collisionSoundBuffer_);
    collisionSound_.setVolume(10);
    swarmSound_.setBuffer(swarmSoundBuffer_);
    swarmSound_.setVolume(5);

    enemy::enemySpeed_ = enemySpeed_; 
    enemy::maxEnemies_ = totalEnemies_; 
    enemy::enemyspawnInterval_ = spawnInterval_; 
    enemy::enemyScale_ = {1.0f,1.0f};
}

pod::~pod()
{
}

void pod::checkSwarmCollision(playerShip &playership_) {
    for(int i = 0; i < swarm_.size(); i++)
    {
        sf::FloatRect swarmBounds_ = swarm_[i].getGlobalBounds();
        sf::FloatRect playersBounds_ = playership_.getplayerGlobalsBounds();

        if(swarmBounds_.intersects(playersBounds_))
        {
            playerLives playerLives_; 
            playerLives_.decreaseplayerLives();
            swarm_.erase(swarm_.begin() + i);
        }
    }
}

void pod::checkProjectileCollision(std::vector<projectiles>& playershipProjectiles_)
{
    for (int i = 0; i < enemies_.size(); i++) {
        for (int j = 0; j < playershipProjectiles_.size(); j++) {
            sf::FloatRect podsBounds_ = enemies_[i].getGlobalBounds();
            sf::FloatRect projectilesBounds_ = playershipProjectiles_[j].getSprite().getGlobalBounds();
            if (podsBounds_.intersects(projectilesBounds_)) {
                //Remove pod and spawn the swarm 
                collisionSound_.play();
                spawnSwarm(enemies_[i].getPosition());
                enemies_.erase(enemies_.begin() + i);
                playershipProjectiles_.erase(playershipProjectiles_.begin() + j);
                playerScore_.updateScore(podPoints_); 
            }
        }
    }
}

void pod::checkSwarmProjectileCollision(std::vector<projectiles> &playerShipProjectiles_)
{
    if(!swarm_.empty()) {
        for(int i = 0; i < swarm_.size(); i++) {
            for(int j = 0; j < playerShipProjectiles_.size();j++) {
                sf::FloatRect swarmBounds_ = swarm_[i].getGlobalBounds();
                sf::FloatRect projectilesBounds_ = playerShipProjectiles_[j].getSprite().getGlobalBounds();

                if(swarmBounds_.intersects(projectilesBounds_)) {
                    //Remove pod and spawn the swarm 
                    collisionSound_.play();
                    swarm_.erase(swarm_.begin() + i);
                    playerShipProjectiles_.erase(playerShipProjectiles_.begin() + j);
                    playerScore_.updateScore(swarmPoints_);
                }
            }
        }
    }
}

// Add a member function to your pod class to add a single swarm enemy to the swarm vector
void pod::addSwarmEnemy(sf::Vector2f position_) 
{
    swarmSprite_.setPosition(position_);
    swarm_.push_back(swarmSprite_);
}

void pod::spawnSwarm(sf::Vector2f podPosition_) 
{
    std::vector<sf::Vector2f> swarmPositions_ = {
        sf::Vector2f(0.0f, -40.0f),
        sf::Vector2f(0.0f, 40.0f),
        sf::Vector2f(5.0f, 0.0f)
    };

    for (const sf::Vector2f& position_ : swarmPositions_) {
        sf::Vector2f swarmEnemyPosition_ = podPosition_ + position_;
        addSwarmEnemy(swarmEnemyPosition_);
    }
}

std::vector<sf::Sprite>& pod::getSwarmSprites()
{
    return swarm_;
}

void pod::moveSwarm()
{
    float speedMultiplier = 0.5; 
    for(auto& moveSwarm_ : swarm_) {
        auto angleSwarm_ = (atan2((playerPosition_.y + 20.0f) - moveSwarm_.getPosition().y, (playerPosition_.x + 30.0f) - moveSwarm_.getPosition().x));
        moveSwarm_.move(speedMultiplier*swarmSpeed_*cos(angleSwarm_)*enemy::dt_, speedMultiplier*swarmSpeed_*sin(angleSwarm_)*enemy::dt_);
        swarmSound_.play();
        speedMultiplier+=0.5;
    }
}

void pod::updatePods()
{
    updateEnemies();
    moveSwarm();
}

void pod::display(sf::RenderWindow &window_)
{
    // Display Pods
    if(!enemy::enemies_.empty()) {
        for (auto& currentPod_ : enemy::enemies_) {
            window_.draw(currentPod_);
        }
    }

    // Display Pods Swarm 
    if(!swarm_.empty())
    {
        for (auto& currentSwarm_ : swarm_) {
            window_.draw(currentSwarm_);
        }
    }
}

void pod::resetPods()
{
    enemies_.clear();
    swarm_.clear();
    enemy::enemyCounter_ = 0;
}

void pod::resetSpawnTimer()
{
    previousTime_ = clock();
}