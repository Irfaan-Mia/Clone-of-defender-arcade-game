#include "enemies.h"

enemy::enemy()
{
    previousTime_ = clock(); 
}

enemy::~enemy()
{
}

void enemy::addEnemy(sf::Sprite enemy)
{
    enemies_.push_back(enemy);
}

std::vector<sf::Sprite>& enemy::getEnemySprites()
{
    return enemies_;
}

bool enemy::checkCollision(const sf::Sprite& newEnemy_, const std::vector<sf::Sprite>& existingEnemies_) 
{
    // Iterate through each existing enemy
    for (const auto& existingEnemy_ : existingEnemies_) 
    {
        // Calculate the bounds of the new enemy and the existing enemy
        sf::FloatRect newEnemyBounds_ = newEnemy_.getGlobalBounds();
        sf::FloatRect existingEnemyBounds_ = existingEnemy_.getGlobalBounds();

        if (newEnemyBounds_.intersects(existingEnemyBounds_)) 
        {
            return true; // Collision detected
        }
    }

    return false; // Else no collision detected
}

void enemy::createEnemy() 
{
    // Create a new lander sprite
    sf::Sprite newEnemy_(enemyTexture_);
    newEnemy_.setScale(enemyScale_);
    auto topBorder_ = windowSize_.y * 0.17;

    // Randomize lander position
    auto collisionDetected = true;
    while (collisionDetected)
    {
        auto randX_ = static_cast<float>(std::rand() % (3000 - 100)); 
        auto randY_ = static_cast<float>(std::rand() % (windowSize_.y - 200));
        newEnemy_.setPosition(randX_, randY_ + topBorder_);
        collisionDetected = checkCollision(newEnemy_,enemies_);
    }
        
    // Add the new enemy sprite to the vector
    //enemies_.push_back(newEnemy_);
    addEnemy(newEnemy_);
}

void enemy::enemyDirection()
{
    // Create a random direction of movement for the new enemy
    auto angle_ = static_cast<float>(std::rand() % 360);
    auto xDirection_ = enemySpeed_ * cos(angle_ * pi / 180.0f); 
    auto yDirection_ = enemySpeed_ * sin(angle_ * pi / 180.0f);

    xDirections_.push_back(xDirection_);
    yDirections_.push_back(yDirection_);
}

void enemy::spawnEnemy()
{
    if (checkSpawnTimer() and enemyCounter_ < maxEnemies_)
    {
        createEnemy();
        enemyDirection();
        enemyCounter_++;
    }
}

void enemy::moveEnemies()
{
    auto topBorder_ = windowSize_.y * 0.17;
    for (auto i = 0; i < enemies_.size(); i++) 
    {
        sf::Vector2f position_ = enemies_[i].getPosition();
        float xDirection_ = xDirections_[i];
        float yDirection_ = yDirections_[i];
        sf::FloatRect enenmyBounds_ = enemies_[i].getGlobalBounds();

        // Check if the enemy hits the left or right edge of the window
        if (position_.x <= 0 || position_.x + enenmyBounds_.width >= windowSize_.x) 
        {
            xDirection_ = -xDirection_;
            xDirections_[i] = xDirection_;
        }

        // Check if the enemy hits the top or bottom edge of the window
        if (position_.y <= topBorder_ || position_.y + enenmyBounds_.height >= windowSize_.y) 
        {
            yDirection_ = -yDirection_;
            yDirections_[i] = yDirection_;
        }
        enemies_[i].move(xDirection_*dt_, yDirection_*dt_);
    }
}

bool enemy::checkSpawnTimer()
{
    if (clock() - previousTime_ >= enemyspawnInterval_) 
    {
        previousTime_ = clock();
        return true; 
    }
    return false; 
}

bool enemy::checkSafeSpawn(float randX_, float randY_){
    if (playerPosition_.x + enemySpawnOffset < randX_ || playerPosition_.x - enemySpawnOffset < randY_)
    {
        if (playerPosition_.y + enemySpawnOffset < randY_ || playerPosition_.y - enemySpawnOffset > randY_)
        {
            return true; 
        }
    }
    return false;
}

bool enemy::hasPlayerCollision(playerShip &playerShip_) 
{
    // Check ship collision with enemy
    for (auto i = 0; i < enemies_.size(); i++) {
        sf::FloatRect enemyBounds_ = enemies_[i].getGlobalBounds();
        sf::FloatRect playersBounds_ = playerShip_.getplayerGlobalsBounds();

        if (enemyBounds_.intersects(playersBounds_)) {
            enemies_.erase(enemies_.begin() + i);
            return true;
        }
    }

    return false;
}

void enemy::checkPlayerCollision(playerShip &playerShip_)
{
    if (hasPlayerCollision(playerShip_)) 
    {
        playerLives playerlives_; 
        collisionSound_.play();
        playerlives_.eliminatePlayer();
    }
}

void enemy::checkProjectileCollision(std::vector<projectiles> &playershipProjectiles_)
{
        for (int i = 0; i < enemies_.size(); i++) {
        for (int j = 0; j < playershipProjectiles_.size(); j++) {
            sf::FloatRect enemyBounds_ = enemies_[i].getGlobalBounds();
            sf::FloatRect projectilesBounds_ = playershipProjectiles_[j].getSprite().getGlobalBounds();
            if (enemyBounds_.intersects(projectilesBounds_)) {
                collisionSound_.play();
                enemies_.erase(enemies_.begin() + i);
                playershipProjectiles_.erase(playershipProjectiles_.begin() + j);
            }
        }
    }
}

void enemy::updateEnemies()
{
    spawnEnemy();
    moveEnemies();
}

void enemy::setDeltaTime(float deltaTime_)
{
    dt_ = deltaTime_;
}

void enemy::setPlayersPosition(sf::Vector2f playersPosition_)
{
    playerPosition_ = playersPosition_;
}

bool enemy::defeatedEnemies()
{
    if (enemies_.size() == 0 and maxEnemies_ == enemyCounter_)
    {
        return true;
    } else return false;
}

std::pair<std::vector<float>, std::vector<float>> enemy::getXAndYDirections()
{
    return std::make_pair(xDirections_, yDirections_);
}

