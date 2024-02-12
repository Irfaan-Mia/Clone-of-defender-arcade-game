/** \file asteroids.cpp
*/

/* Header Files */
#include "asteroids.h"

asteroids::asteroids()
{
    if (!enemyTexture_.loadFromFile("resources/asteroid.png")) 
    {
        std::cerr << "ERROR::LOADING ASTEROID TEXTURE" << std::endl;
        return;
    }
    
    if (!collisionSoundBuffer_.loadFromFile("resources/ship-collision.wav")) 
    {
        std::cerr << "ERROR::LOADING SHIP COLLISION SOUND" << std::endl;
        return;
    }

    collisionSound_.setBuffer(collisionSoundBuffer_);
    collisionSound_.setVolume(10);

    enemy::enemySpeed_ = asteroidSpeed_; 
    enemy::maxEnemies_ = totalAsteroids_; 
    enemy::enemyspawnInterval_ = spawnInterval_; 
    enemy::enemyScale_ = {0.01f,0.01f};
}

asteroids::~asteroids()
{
}

void asteroids::createEnemy() 
{
    for (int i = 0; i < 30; ++i) 
    {
        // Create a new asteroid sprite
        sf::Sprite newEnemy_(enemyTexture_);
        newEnemy_.setScale(enemyScale_);
        auto topBorder_ = windowSize_.y * 0.17;

        // Randomize asteroid position along the x-axis, but keep y constant at the top border
        auto collisionDetected = true;
        while (collisionDetected)
        {
            auto randX_ = static_cast<float>(std::rand() % (3000 - 100)); 
            newEnemy_.setPosition(randX_, (topBorder_ + 10));
            collisionDetected = checkCollision(newEnemy_,enemies_);
        }

        // Add the new asteroid sprite to the vector
        addEnemy(newEnemy_);
        enemyDirection();
    }
}

void asteroids::enemyDirection()
{
    // Set a fixed direction of movement for the new enemy
    auto angle_ = 45.0f; // 45 degrees corresponds to moving from top left to bottom right
    auto xDirection_ = asteroidSpeed_ * cos(angle_ * pi / 180.0f); 
    auto yDirection_ = asteroidSpeed_ * sin(angle_ * pi / 180.0f);

    xDirections_.push_back(xDirection_);
    yDirections_.push_back(yDirection_);
}

void asteroids::moveEnemies()
{
    auto topBorder_ = windowSize_.y * 0.17;
    auto bottomBorder_ = windowSize_.y;

    for (auto i = 0; i < enemies_.size(); i++) 
    {
        sf::Vector2f position_ = enemies_[i].getPosition();
        float xDirection_ = xDirections_[i];
        float yDirection_ = yDirections_[i];
        sf::FloatRect enemyBounds_ = enemies_[i].getGlobalBounds();

        // Check if the enemy hits the left or right edge of the window
        if (position_.x <= 0 || position_.x + enemyBounds_.width >= windowSize_.x) 
        {
            xDirection_ = -xDirection_;
            xDirections_[i] = xDirection_;
        }

        // Check if the enemy hits the top or bottom edge of the window
        if (position_.y <= topBorder_ || position_.y + enemyBounds_.height >= bottomBorder_)
        {
            // If the enemy has reached the bottom of the screen, remove it
            if (position_.y + enemyBounds_.height >= bottomBorder_)
            {
                enemies_.clear();
                xDirections_.clear();
                yDirections_.clear();
                enemy::enemyCounter_ = 0;
                previousTime_ = clock();
            }
            else
            {
                yDirection_ = -yDirection_;
                yDirections_[i] = yDirection_;
            }
        }
        enemies_[i].move(xDirection_*dt_, yDirection_*dt_);
    }
}

void asteroids::spawnEnemy()
{
    if (checkSpawnTimer() and enemyCounter_ < maxEnemies_)
    {
        createEnemy();
        enemyCounter_++;
    }
}


void asteroids::resetAsteroids()
{
    enemies_.clear();    
    enemy::enemyCounter_ = 0; 
    enemy::previousTime_ = clock();
}

void asteroids::displayAsteroids(sf::RenderWindow& window_){
    if (!enemy::enemies_.empty()) 
    {
        for (auto& currentAlien_ : enemy::enemies_) {
            window_.draw(currentAlien_);
        }
    }
}