#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include "playerShip.h"
#include "projectiles.h"
#include "PlayerProjectiles.h"
#include "enemies.h"
#include "alien.h"
#include "pod.h"
#include "playerShield.h"
#include "asteroids.h"
#include "landersMissiles.h"
#include "scrolling.h"
#include "score.h"
#include "playerLives.h"
#include "handlingHumanoids.h"

// ------------- Tests for Player Ship ----------------
TEST_CASE("Players ship spawned in screen")
{
    playerShip test; 
    sf::Vector2f ship_pos = test.getPos();
    CHECK(ship_pos.x < 3000.0f); 
    CHECK(ship_pos.x > 0.0f); 
    CHECK(ship_pos.y > 0.0f); 
    CHECK(ship_pos.y < 750.0f);
}

TEST_CASE("Players ship moves up with W key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::W,true);
    test.update();
    CHECK(test.getPos().x == initial_pos.x);
    CHECK(test.getPos().y + test.getmovementSpeed().y*dt == initial_pos.y);
}

TEST_CASE("Players ship moves down with S key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::S,true);
    test.update();
    CHECK(test.getPos().x == initial_pos.x);
    CHECK(test.getPos().y - test.getmovementSpeed().y*dt == initial_pos.y);
}

TEST_CASE("Players ship moves left with A key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::A,true);
    test.update();
    CHECK(test.getPos().x + test.getmovementSpeed().x*dt == initial_pos.x);
    CHECK(test.getPos().y == initial_pos.y);
}

TEST_CASE("Players ship move right with D key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement 
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::D,true);
    test.update();
    CHECK(test.getPos().x - test.getmovementSpeed().x*dt == initial_pos.x);
    CHECK(test.getPos().y == initial_pos.y);
}

TEST_CASE("Check release of key prevents combined motion by returning to original position")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::D,true);
    test.update();
    test.processEvent(sf::Keyboard::D,false);
    test.update();
    test.processEvent(sf::Keyboard::A,true);
    test.update();
    CHECK(test.getPos().x == initial_pos.x); 
    CHECK(test.getPos().y == initial_pos.y);
}

TEST_CASE("Players ship moves diagonally to the right and up with W and D key")
{
    playerShip test;
    float dt = 0.01f; //Time based movement 
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::W,true);
    test.processEvent(sf::Keyboard::D,true);
    test.update();
    CHECK(test.getPos().x > initial_pos.x);
    CHECK(test.getPos().y < initial_pos.y);
}

TEST_CASE("Players ship moves diagonally to the right and down with S and D key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::S,true);
    test.processEvent(sf::Keyboard::D,true);
    test.update();
    CHECK(test.getPos().x > initial_pos.x);
    CHECK(test.getPos().y > initial_pos.y);
}

TEST_CASE("Players ship moves diagonally to the left and down with A and S key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement 
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::S,true);
    test.processEvent(sf::Keyboard::A,true);
    test.update();
    CHECK(test.getPos().x < initial_pos.x);
    CHECK(test.getPos().y > initial_pos.y);
}

TEST_CASE("Players ship moves diagonally to the left and up with A and W key")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    test.processEvent(sf::Keyboard::W,true);
    test.processEvent(sf::Keyboard::A,true);
    test.update();
    CHECK(test.getPos().x < initial_pos.x);
    CHECK(test.getPos().y < initial_pos.y);
}

TEST_CASE("Projectile of player ship made when space key is pressed")
{
    PlayerProjectiles PlayerProjectiles_; 
    PlayerProjectiles_.shootbullet({1.0f,0.0f},{300.0f,300.0f},sf::Keyboard::Key::Space);
    CHECK(PlayerProjectiles_.numberProjectiles() == 1);
}

TEST_CASE("Player ship able to wrap around from left to right side of game screen")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    sf::Vector2f movementSpeed = test.getmovementSpeed();
    int counter = static_cast<int>(initial_pos.x/(movementSpeed.x*dt)); 
    while(counter != 0)
    {
        test.processEvent(sf::Keyboard::A,true);
        test.update();
        counter--; 
    }
    test.processEvent(sf::Keyboard::A,true);
    test.update();
    CHECK(test.getPos().x > initial_pos.x);
}

TEST_CASE("Player ship able to wrap around from right to left side of game screen")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    sf::Vector2f movementSpeed = test.getmovementSpeed();
    int counter = static_cast<int>(initial_pos.x/(movementSpeed.x*dt)); 
    while(counter != 0)
    {
        test.processEvent(sf::Keyboard::D,true);
        test.update();
        counter--; 
    }
    test.processEvent(sf::Keyboard::D,true);
    test.update();
    CHECK(test.getPos().x < initial_pos.x);
}

TEST_CASE("Player ship unable to move further than upper boundary")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    sf::Vector2f movementSpeed = test.getmovementSpeed();
    int counter = static_cast<int>(initial_pos.x/(movementSpeed.x*dt)); 
    while(counter != 0)
    {
        test.processEvent(sf::Keyboard::W,true);
        test.update();
        counter--; 
    }
    sf::Vector2f temp = test.getPos();
    test.processEvent(sf::Keyboard::W,true);
    test.update();
    CHECK(temp.x == test.getPos().x);
}

TEST_CASE("Player ship unable to move further than lower boundary")
{
    playerShip test; 
    float dt = 0.01f; //Time based movement
    test.setdt(dt);
    sf::Vector2f initial_pos = test.getPos();
    sf::Vector2f movementSpeed = test.getmovementSpeed();
    int counter = static_cast<int>(initial_pos.x/(movementSpeed.x*dt)); 
    while(counter != 0)
    {
        test.processEvent(sf::Keyboard::S,true);
        test.update();
        counter--; 
    }
    sf::Vector2f temp = test.getPos();
    test.processEvent(sf::Keyboard::S,true);
    test.update();
    CHECK(temp.x == test.getPos().x);
}

// ------------- Tests for Projectiles ----------------

// ------------- Tests for Projectiles ----------------
TEST_CASE("Check if projectile is made on screen")
{
    PlayerProjectiles playerProjectiles_;
    playerProjectiles_.shootbullet({1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
    playerProjectiles_.setdt(0.01f);
    CHECK(playerProjectiles_.numberProjectiles() == 1);
    CHECK(playerProjectiles_.getPlayerProjectiles()[0].getSprite().getPosition().x < 3000.0f);
    CHECK(playerProjectiles_.getPlayerProjectiles()[0].getSprite().getPosition().x > 0.0f);
    CHECK(playerProjectiles_.getPlayerProjectiles()[0].getSprite().getPosition().y > 0.0f);
    CHECK(playerProjectiles_.getPlayerProjectiles()[0].getSprite().getPosition().y < 750.0f);
}

TEST_CASE("Check projectile has moved")
{
   PlayerProjectiles playerProjectiles_;
   playerProjectiles_.shootbullet({1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
   playerProjectiles_.setdt(0.01f);
   auto initialPos_ = playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position();
   playerProjectiles_.update();
   CHECK(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().x != initialPos_.x);
   CHECK(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().y == initialPos_.y);
}

TEST_CASE("Check projectile moves right with specified direction")
{
   PlayerProjectiles playerProjectiles_;
   playerProjectiles_.shootbullet({1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
   playerProjectiles_.setdt(0.01f);
   auto initialPos_ = playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position();
   playerProjectiles_.update();
   CHECK(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().x > initialPos_.x);
   CHECK(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().y == initialPos_.y);
}

TEST_CASE("Check projectile moves left with specified direction")
{
   PlayerProjectiles playerProjectiles_;
   playerProjectiles_.shootbullet({-1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
   playerProjectiles_.setdt(0.01f);
   auto initialPos_ = playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position();
   playerProjectiles_.update();
   CHECK(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().x < initialPos_.x);
   CHECK(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().y == initialPos_.y);
}

TEST_CASE("Check collision of players projectile with alien")
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-lander.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f); 
   
    PlayerProjectiles playerProjectiles_;
    playerProjectiles_.shootbullet({1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
    playerProjectiles_.setdt(0.01f);
    CHECK(playerProjectiles_.numberProjectiles() == 1);

    alien alien_;
    enemy_.setPosition(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position());
    alien_.addEnemy(enemy_);
    alien_.checkProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    CHECK(playerProjectiles_.numberProjectiles() == 0);
}

TEST_CASE("Check collision of players projectile with pod")
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f); 
   
    PlayerProjectiles playerProjectiles_;
    playerProjectiles_.setdt(0.01f);
    playerProjectiles_.shootbullet({1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
    CHECK(playerProjectiles_.numberProjectiles() == 1);
    
    pod pod_;
    enemy_.setPosition(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position());
    pod_.addEnemy(enemy_);
    pod_.checkProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    CHECK(playerProjectiles_.numberProjectiles() == 0);
}

TEST_CASE("Check collision of players projectile with swarm")
{
    pod pod_; 
    pod_.spawnSwarm({300.0f,300.0f});
    CHECK(pod_.getSwarmSprites().size() == 3);
    PlayerProjectiles playerProjectiles_;
    playerProjectiles_.shootbullet({1.0f,0.0f},{pod_.getSwarmSprites()[0].getPosition().x,pod_.getSwarmSprites()[0].getPosition().y - 25.0f},sf::Keyboard::Space);
    playerProjectiles_.setdt(0.01f);
    pod_.checkSwarmProjectileCollision(playerProjectiles_.getPlayerProjectiles());
    CHECK(pod_.getSwarmSprites().size() == 2);
}

TEST_CASE("Check projectile deleted at left border")
{
    PlayerProjectiles playerProjectiles_;
    playerProjectiles_.shootbullet({-1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
    playerProjectiles_.setdt(0.01f);
    sf::RectangleShape line1_; 
    auto lineWidth_ = 5;
    line1_.setSize(sf::Vector2f(lineWidth_, 750.0f));  
    line1_.setPosition(1000.0f,0.0f);
    sf::RectangleShape line2_;
    line2_.setSize(sf::Vector2f(lineWidth_, 750.0f));
    line2_.setPosition(1500.0f,0.0f);
    playerProjectiles_.setprojectileBorder(line1_,line2_);
    CHECK(playerProjectiles_.getPlayerProjectiles().size() == 1);
    while(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().x > 1000.0f)
    {
        playerProjectiles_.update();
    }   
    playerProjectiles_.update();
    CHECK(playerProjectiles_.getPlayerProjectiles().size() == 0);
}

TEST_CASE("Check projectile deleted at right border")
{
    PlayerProjectiles playerProjectiles_;
    playerProjectiles_.shootbullet({1.0f,0.0f},{1350.0f,350.0f},sf::Keyboard::Space);
    playerProjectiles_.setdt(0.01f);
    sf::RectangleShape line1_; 
    auto lineWidth_ = 5;
    line1_.setSize(sf::Vector2f(lineWidth_, 750.0f));  
    line1_.setPosition(1000.0f,0.0f);
    sf::RectangleShape line2_;
    line2_.setSize(sf::Vector2f(lineWidth_, 750.0f));
    line2_.setPosition(1500.0f,0.0f);
    playerProjectiles_.setprojectileBorder(line1_,line2_);
    CHECK(playerProjectiles_.getPlayerProjectiles().size() == 1);
    while(playerProjectiles_.getPlayerProjectiles()[0].get_projectile_position().x < 1500.0f)
    {
        playerProjectiles_.update();
    }   
    playerProjectiles_.update();
    CHECK(playerProjectiles_.getPlayerProjectiles().size() == 0);
}

// // ------------- Tests for Players fuel ----------------

TEST_CASE("Fuel is spawned within the game screen")
{
    fuel test; 
    sf::Sprite temp; 
    test.addfuel(temp);
    CHECK(test.getfuel().size() == 1);
    test.resetFuel();
}

TEST_CASE("Fuel is decreased by set value")
{
    fuel test; 
    int initialFuel = test.gettotalFuel(); 
    test.decrementfuel();
    CHECK(test.gettotalFuel() != initialFuel);
    test.resetFuel();
}

TEST_CASE("Check if player has fuel after using it")
{
    fuel test; 
    sf::Sprite temp; 
    test.addfuel(temp);
    for(int i = 0 ; i < 20; i++)
    {
        test.decrementfuel();
    }
    CHECK(test.gettotalFuel() == 0);
    CHECK_FALSE(test.doesplayerhaveFuel());
    test.resetFuel();
}

TEST_CASE("Check player collision with fuel")
{
    fuel Fuel; 
    sf::Sprite test; 
    sf::Texture test_texture; 
    test_texture.loadFromFile("resources/fuel.png");
    test.setTexture(test_texture);
    test.setPosition(300.0f,300.0f);
    Fuel.addfuel(test);
    sf::Sprite temp; 
    sf::Texture temp_texture; 
    temp_texture.loadFromFile("resources/ship_left.png");
    temp.setTexture(temp_texture);
    temp.setScale(1.0f,1.0f);
    temp.setPosition(300.0f,300.0f);
    Fuel.decrementfuel();
    Fuel.checkcollisionwithFuel(temp.getGlobalBounds());
    CHECK(Fuel.gettotalFuel() == 100);
    Fuel.resetFuel();
}

TEST_CASE("Check spawning of fuel causes no overlap")
{
    fuel Fuel; 
    sf::Sprite test1; 
    sf::Texture test1_texture; 
    test1_texture.loadFromFile("resources/fuel.png");
    test1.setTexture(test1_texture);
    test1.setScale(1.0f,1.0f);
    test1.setPosition(200.0f,300.0f);
    Fuel.addfuel(test1);
    sf::Sprite test2; 
    test2.setTexture(test1_texture);
    test2.setScale(1.0f,1.0f);
    test2.setPosition(300.0f,300.0f);
    CHECK(Fuel.checkfuelOverlap(test2,1.0f,1.0f));
    Fuel.resetFuel();
}

TEST_CASE("Check spawning of fuel if overlapping")
{
    fuel Fuel; 
    sf::Sprite test1; 
    sf::Texture test1_texture; 
    test1_texture.loadFromFile("resources/fuel.png");
    test1.setTexture(test1_texture);
    test1.setScale(1.0f,1.0f);
    test1.setPosition(300.0f,300.0f);
    Fuel.addfuel(test1);
    sf::Sprite test2; 
    test2.setTexture(test1_texture);
    test2.setScale(1.0f,1.0f);
    test2.setPosition(300.0f,300.0f);
    CHECK(Fuel.checkfuelOverlap(test2,1.0f,1.0f));
    Fuel.resetFuel();
}

// // ------------- Tests for Enemy Class ----------------

// //Note: movement for enemy class is not done as it is done for children of class which is alien and pod class which are actually displayed in the game
TEST_CASE("An enemy sprite is created") 
{
    enemy testEnemy_;
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    testEnemy_.addEnemy(enemy_);
    testEnemy_.addEnemy(enemy_);

    const std::vector<sf::Sprite>& enemySprites_ = testEnemy_.getEnemySprites();

    CHECK(enemySprites_.size() == 2);
}

TEST_CASE("An enemy sprite is created within window application") 
{
    enemy testEnemy_;
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(400,200);
    testEnemy_.addEnemy(enemy_);
    sf::Vector2u windowSize_(800, 600);

    const std::vector<sf::Sprite>& enemySprites_ = testEnemy_.getEnemySprites();

    CHECK(enemySprites_.size() > 0);
    for (const sf::Sprite& enemySprite_ : enemySprites_) {
        sf::Vector2f spritePosition_ = enemySprite_.getPosition();
        sf::FloatRect spriteBounds_ = enemySprite_.getGlobalBounds();
        CHECK(spritePosition_.x >= 0);
        CHECK(spritePosition_.y >= 0);
        CHECK(spritePosition_.x + spriteBounds_.width <= windowSize_.x);
        CHECK(spritePosition_.y + spriteBounds_.height <= windowSize_.y);
    }
}

TEST_CASE("Check for collision between player's ship and the enemy")
{
    enemy testEnemy_;
    playerShip playerShip_; 
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    testEnemy_.addEnemy(enemy_);

    bool collisionDetected_ = testEnemy_.hasPlayerCollision(playerShip_);
    CHECK(collisionDetected_ == true);
}

// // ------------- Tests for Alien Class ----------------

TEST_CASE("An alien sprite is created") 
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);

    alien alien_;
    alien_.addEnemy(enemy_);

    const std::vector<sf::Sprite>& alienSprites_ = alien_.getEnemySprites();

    CHECK(alienSprites_.size() == 1);
}

TEST_CASE("Check for collision between player's ship and the alien")
{
    playerShip playerShip_; 
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    alien alien_;
    alien_.addEnemy(enemy_);

    bool collisionDetected_ = alien_.hasPlayerCollision(playerShip_);
    CHECK(collisionDetected_ == true);
}

TEST_CASE("Check that collision between player ship and the alien decreases player ship's life")
{
    playerShip playerShip_; 
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    alien alien_;
    alien_.addEnemy(enemy_);

    alien_.checkPlayerCollision(playerShip_);
    int initialLives_ = 3; 
    CHECK(playerLives_.getplayerLives() == initialLives_ - 3); // all lives are expected to be lost
}

TEST_CASE("Check for a collision with the landers missile and the player ship")
{
    playerShip playerShip_; 
    playerShield playershield;
    sf::Sprite bullet_; 
    sf::Texture bulletTexture_;
    bulletTexture_.loadFromFile("resources/arrow.png");
    bullet_.setTexture(bulletTexture_);
    bullet_.setPosition(playerShip_.getPos());

    alien alien_; 
    alien_.setPlayersPosition(playerShip_.getPos());
    alien_.addBullet(bullet_);

    playerShip_.processEvent(sf::Keyboard::Space,true);

    bool collisionDetected_ = alien_.hasMissilesCollision(playerShip_);
    CHECK(collisionDetected_ == true);
}

TEST_CASE("Check that a collision with the landers missile and decreases the player's life")
{
    playerShip playerShip_; 
    playerShield playershield;
    sf::Sprite bullet_; 
    sf::Texture bulletTexture_;
    bulletTexture_.loadFromFile("resources/arrow.png");
    bullet_.setTexture(bulletTexture_);
    bullet_.setPosition(playerShip_.getPos());

    alien alien_; 
    alien_.setPlayersPosition(playerShip_.getPos());
    alien_.addBullet(bullet_);

    playerLives playerLives_;
    playerLives_.resetplayerLives();
    alien_.checkMissilesCollision(playerShip_);
    int initialLives_ = 3; 
    CHECK(playerLives_.getplayerLives() == initialLives_ - 1); // one life is expected to be lost
}

TEST_CASE("Check that Aliens move") 
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    float dt = 0.01f; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    
    alien alien_;
    alien_.setDeltaTime(dt);
    alien_.addEnemy(enemy_);
    alien_.getEnemySprites()[0].setPosition(100, 100);

    alien_.enemyDirection();
    for (auto i = 0; i < 10; i++)
    {
        alien_.moveEnemies();
    }
        
    sf::Vector2f newPosition = alien_.getEnemySprites()[0].getPosition();
    CHECK(newPosition.x != 100.0f);
}

TEST_CASE("Landers missiles move in specific direction")
{
    landersMissiles landermissile; 
    landermissile.addlanderMissile({0.0f,0.0f},{300.0f,300.0f});
    landermissile.setdt(0.01f);
    landermissile.moveBullets();
    CHECK(landermissile.getbullets()[0].getSprite().getPosition().x != 0.0f);
    CHECK(landermissile.getbullets()[0].getSprite().getPosition().x != 0.0f);
}
// // ------------- Tests for Pod Class ----------------

TEST_CASE("A pod sprite is created") 
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    pod pod_;
    pod_.addEnemy(enemy_);
    pod_.addEnemy(enemy_);

    const std::vector<sf::Sprite>& podSprites_ = pod_.getEnemySprites();

    CHECK(podSprites_.size() == 2);
}

TEST_CASE("Spawn a swarm around a pod enemy")
{
    pod pod_;
    auto initialSwarmSize_ = pod_.getSwarmSprites().size();
    sf::Vector2f podPosition_(100.0f, 100.0f);
    pod_.spawnSwarm(podPosition_);

    auto updatedSwarmSize_ = pod_.getSwarmSprites().size();
    
    CHECK(updatedSwarmSize_ == initialSwarmSize_ + 3);
}

TEST_CASE("Check swarm move")
{
    pod pod_;
    auto initialSwarmSize_ = pod_.getSwarmSprites().size();
    sf::Vector2f podPosition_(100.0f, 100.0f);
    pod_.spawnSwarm(podPosition_);
    pod_.setDeltaTime(0.01f);
    pod_.setPlayersPosition({200.0f,200.0f});
    std::vector<sf::Vector2f> initialswarmpos;
    for(auto i = 0; i < pod_.getSwarmSprites().size(); i++)
    {
        initialswarmpos.push_back(pod_.getSwarmSprites()[i].getPosition());
    }
    pod_.moveSwarm();
    for(auto i = 0 ;i < pod_.getSwarmSprites().size(); i++)
    {
        CHECK(initialswarmpos[i].x != pod_.getSwarmSprites()[i].getPosition().x);
        CHECK(initialswarmpos[i].y != pod_.getSwarmSprites()[i].getPosition().y);
    }
}

TEST_CASE("Check swarm move towards player position")
{
    pod pod_;
    auto initialSwarmSize_ = pod_.getSwarmSprites().size();
    sf::Vector2f podPosition_(100.0f, 100.0f);
    pod_.spawnSwarm(podPosition_);
    pod_.setDeltaTime(0.01f);
    pod_.setPlayersPosition({200.0f,200.0f});
    std::vector<sf::Vector2f> initialswarmpos;
    for(auto i = 0; i < pod_.getSwarmSprites().size(); i++)
    {
        initialswarmpos.push_back(pod_.getSwarmSprites()[i].getPosition());
    }
    pod_.moveSwarm();
    for(auto i = 0 ;i < pod_.getSwarmSprites().size(); i++)
    {
        CHECK(initialswarmpos[i].x < pod_.getSwarmSprites()[i].getPosition().x);
        CHECK(initialswarmpos[i].y < pod_.getSwarmSprites()[i].getPosition().y);
    }  
}

TEST_CASE("Check that Pods moves")
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    float dt = 0.01f; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);

    pod pod_;
    pod_.setDeltaTime(dt);
    pod_.addEnemy(enemy_);
    pod_.getEnemySprites()[0].setPosition(100, 100);

    pod_.enemyDirection();
    for (auto i = 0; i < 10; i++)
    {
        pod_.moveEnemies();
    }

    sf::Vector2f newPosition = pod_.getEnemySprites()[0].getPosition();
    CHECK(newPosition.x != 100.0f);
}

TEST_CASE("Check for collision between player's ship and the pod")
{
    playerShip playerShip_; 
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    pod pod_;
    pod_.addEnemy(enemy_);

    bool collisionDetected_ = pod_.hasPlayerCollision(playerShip_);
    CHECK(collisionDetected_ == true);
}

TEST_CASE("Check that collision between player ship and the pod decreases player ship's life")
{
    playerShip playerShip_; 
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    pod pod_;
    pod_.addEnemy(enemy_);

    playerLives playerLives_;
    //Reset to ensure collision detection is correct
    playerLives_.resetplayerLives();
    pod_.checkPlayerCollision(playerShip_);
    int initialLives_ = 3; 
    CHECK(playerLives_.getplayerLives() == initialLives_ - 3); // all lives are expected to be lost
}

TEST_CASE("Check for collision between player's ship and the swarm")
{
    playerShip playerShip_; 
    pod pod_;
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    auto initialLives_ = 3;

    pod_.spawnSwarm(playerShip_.getPos());
    pod_.checkSwarmCollision(playerShip_);

    CHECK(playerLives_.getplayerLives() == initialLives_ - 1); // one life is expected to be lost
}

// // ------------- Tests for Players Shield Class ----------------

TEST_CASE("Check player can activate shield")
{
    playerShield shield; 
    shield.resetShields();
    shield.processInput(sf::Keyboard::V);
    CHECK(shield.isshieldActive());
    shield.resetShields();
}

TEST_CASE("Player can move with activated shield")
{
    //Not really required due to implementation just switching textures and not affecting general movement of player
    playerShield playershield; 
    playershield.activateShield();
    playerShip playership;
    playership.setdt(0.01f);
    playership.processEvent(sf::Keyboard::A,true); 
    auto initialPlayerPos = playership.getPos();
    playership.update();
    CHECK(playership.getPos().x != initialPlayerPos.x);
    CHECK(playership.getPos().y == initialPlayerPos.y);
    playership.processEvent(sf::Keyboard::S,true);
    playership.update();
    CHECK(playership.getPos().x != initialPlayerPos.x);
    CHECK(playership.getPos().y != initialPlayerPos.y);
    playership.processEvent(sf::Keyboard::D,true);
    playership.update();
    playership.processEvent(sf::Keyboard::S,true);
    playership.update();
    CHECK(playership.getPos().x != initialPlayerPos.x);
    CHECK(playership.getPos().y != initialPlayerPos.y);
    playershield.resetShields();
}

TEST_CASE("Check shield can be deactivated")
{
    playerShield shield; 
    shield.resetShields();
    shield.processInput(sf::Keyboard::V);
    CHECK(shield.isshieldActive());
    shield.deactivateShield();
    CHECK_FALSE(shield.isshieldActive());
    shield.resetShields();
}

TEST_CASE("Check shield can only be used a number of times")
{
    playerShield shield; 
    shield.resetShields();
    shield.processInput(sf::Keyboard::V);
    CHECK(shield.isshieldActive());
    shield.deactivateShield();
    shield.processInput(sf::Keyboard::V);
    CHECK(shield.isshieldActive()); 
    shield.deactivateShield();
    shield.processInput(sf::Keyboard::V); 
    CHECK(shield.isshieldActive());
    shield.deactivateShield();
    CHECK_FALSE(shield.isshieldActive());
    shield.processInput(sf::Keyboard::V);
    CHECK_FALSE(shield.isshieldActive()); 
    shield.resetShields();
}

TEST_CASE("Check collision with lander deactivates shield")
{
    playerShip playership; 
    sf::Sprite enemy; 
    sf::Texture enemy_texture; 
    enemy_texture.loadFromFile("resources/enemy-lander.png");
    enemy.setTexture(enemy_texture);
    enemy.setScale(1.0f,1.0f);
    enemy.setPosition(playership.getPos());
    alien lander; 
    lander.addEnemy(enemy);
    playerShield playershield; 
    playershield.resetShields();
    playershield.activateShield();
    CHECK(playershield.isshieldActive());
    lander.checkPlayerCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
    playershield.resetShields();
}

TEST_CASE("Check collision with lander does not decrease player lives when activated shield")
{
    playerShip playership; 
    sf::Sprite enemy; 
    sf::Texture enemy_texture; 
    playerShield playershield_; 
    playershield_.resetShields();
    enemy_texture.loadFromFile("resources/enemy-lander.png");
    enemy.setTexture(enemy_texture);
    enemy.setScale(1.0f,1.0f);
    enemy.setPosition(playership.getPos());
    alien lander; 
    lander.addEnemy(enemy);
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    playerLives_.getplayerLives(); //Done to ensure collision detection is correct
    auto previousplayerlives = 3;
    playershield_.activateShield();
    CHECK(playerShield::isshieldActive());
    lander.checkPlayerCollision(playership);
    CHECK_FALSE(playerShield::isshieldActive());
    CHECK(playerLives_.getplayerLives() == previousplayerlives);
    playershield_.resetShields();
}

TEST_CASE("Check collision with lander decreases player lives when shield deactivated")
{
    playerShip playership; 
    sf::Sprite enemy; 
    sf::Texture enemy_texture; 
    enemy_texture.loadFromFile("resources/enemy-lander.png");
    enemy.setTexture(enemy_texture);
    enemy.setScale(1.0f,1.0f);
    enemy.setPosition(playership.getPos());
    alien lander; 
    lander.addEnemy(enemy);
    playerShield playershield; 
    playershield.resetShields();
    playershield.activateShield();
    playerLives playerLives_; 
    playerLives_.resetplayerLives();
    auto previousplayerlives = 3;
    CHECK(playershield.isshieldActive());
    playershield.deactivateShield();
    lander.checkPlayerCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
    CHECK(playerLives_.getplayerLives() != previousplayerlives);
    playershield.resetShields();
}

TEST_CASE("Check collision with landers missile deactivates shield")
{
    playerShip playership; 
    alien lander; 
    playerShield playershield;
    sf::Sprite bullet; 
    sf::Texture bullet_texture;
    bullet_texture.loadFromFile("resources/arrow.png");
    bullet.setTexture(bullet_texture);
    bullet.setPosition(playership.getPos());
    bullet.setScale(1.0f,1.0f);
    lander.setPlayersPosition(playership.getPos());
    lander.addBullet(bullet);
    playershield.activateShield();
    lander.checkMissilesCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
}

TEST_CASE("Check collision with landers missile decreases player lives when no shield")
{
    playerShip playership; 
    alien lander; 
    playerShield playershield;
    sf::Sprite bullet; 
    sf::Texture bullet_texture;
    bullet_texture.loadFromFile("resources/arrow.png");
    bullet.setTexture(bullet_texture);
    bullet.setPosition(playership.getPos());
    bullet.setScale(1.0f,1.0f);
    lander.setPlayersPosition(playership.getPos());
    lander.addBullet(bullet);
    playershield.activateShield();
    playershield.deactivateShield();
    playerLives playerLives_; 
    playerLives_.resetplayerLives();
    auto previousplayerlives = 3;
    lander.checkMissilesCollision(playership);
    CHECK(previousplayerlives != playerLives_.getplayerLives());
}

TEST_CASE("Check collision with pod deactivates shield")
{
    playerShip playership; 
    sf::Sprite enemy; 
    sf::Texture enemy_texture; 
    enemy_texture.loadFromFile("resources/enemy-pod.png");
    enemy.setTexture(enemy_texture);
    enemy.setScale(1.0f,1.0f);
    enemy.setPosition(playership.getPos());
    pod pod_; 
    pod_.addEnemy(enemy);
    playerShield playershield; 
    playershield.resetShields();
    playershield.activateShield();
    CHECK(playershield.isshieldActive());
    pod_.checkPlayerCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
}

TEST_CASE("Check collision with pod does not decrease player lives when activated shield")
{
    playerShip playership; 
    sf::Sprite enemy; 
    sf::Texture enemy_texture; 
    enemy_texture.loadFromFile("resources/enemy-pod.png");
    enemy.setTexture(enemy_texture);
    enemy.setScale(1.0f,1.0f);
    enemy.setPosition(playership.getPos());
    pod pod_; 
    pod_.addEnemy(enemy);
    playerShield playershield; 
    playershield.resetShields();
    playershield.activateShield();
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    auto previousplayerlives = 3;
    CHECK(playershield.isshieldActive());
    pod_.checkPlayerCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
    CHECK(previousplayerlives == playerLives_.getplayerLives());   
    playershield.resetShields();
}

TEST_CASE("Check collision with pod decreases player lives when shield deactivated")
{
    playerShip playership; 
    sf::Sprite enemy; 
    sf::Texture enemy_texture; 
    enemy_texture.loadFromFile("resources/enemy-pod.png");
    enemy.setTexture(enemy_texture);
    enemy.setScale(1.0f,1.0f);
    enemy.setPosition(playership.getPos());
    pod pod_; 
    pod_.addEnemy(enemy);
    playerShield playershield; 
    playershield.resetShields();
    playershield.activateShield();
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    auto previousplayerlives = 3;
    CHECK(playershield.isshieldActive());
    playershield.deactivateShield();
    pod_.checkPlayerCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
    CHECK(playerLives_.getplayerLives() != previousplayerlives);
}

TEST_CASE("Check collision with swarm does not decrease player lives when activated shield")
{
    playerShip playership; 
    playerShield playershield; 
    playershield.activateShield();
    pod pod_;
    pod_.spawnSwarm(playership.getPos());
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    auto previousplayerlives = 3;
    pod_.checkSwarmCollision(playership);
    CHECK_FALSE(playershield.isshieldActive());
    CHECK(previousplayerlives == playerLives_.getplayerLives());
}

TEST_CASE("Check collision with swarm decreases player live when shield deactivated")
{
    playerShip playership; 
    playerShield playershield; 
    playershield.activateShield();
    pod pod_;
    playershield.deactivateShield();
    playerLives playerLives_;
    playerLives_.resetplayerLives();
    auto playerlives = 3;
    pod_.spawnSwarm(playership.getPos());
    pod_.checkSwarmCollision(playership);
    CHECK(playerlives != playerLives_.getplayerLives());
}
// // ------------- Tests for Asteriod Class ----------------

TEST_CASE("An asteroid sprite is created") 
{
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);

    asteroids asteroids_;
    asteroids_.addEnemy(enemy_);

    const std::vector<sf::Sprite>& asteroidsSprites_ = asteroids_.getEnemySprites();

    CHECK(asteroidsSprites_.size() == 1);
}

TEST_CASE("Asteriods move down the screen")
{
    sf::Sprite asteriod_; 
    sf::Texture enemyTexture_; 
    float dt = 0.01f; 

    enemyTexture_.loadFromFile("resources/asteroid.png");
    asteriod_.setTexture(enemyTexture_);
    asteriod_.setScale(1.0f,1.0f);
    
    asteroids asteriod;
    asteriod.setDeltaTime(dt);
    asteriod.addEnemy(asteriod_);
    asteriod.getEnemySprites()[0].setPosition(100, 100);

    asteriod.enemyDirection();
    for (auto i = 0; i < 10; i++)
    {
        asteriod.moveEnemies();
    }
        
    sf::Vector2f newPosition = asteriod.getEnemySprites()[0].getPosition();
    CHECK(newPosition.y != 100.0f);
}

TEST_CASE("Check for collision between player's ship and the asteroid")
{
    playerShip playerShip_; 
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    asteroids asteroids_;
    asteroids_.addEnemy(enemy_);

    bool collisionDetected_ = asteroids_.hasPlayerCollision(playerShip_);
    CHECK(collisionDetected_ == true);
}

TEST_CASE("Check that collision between player ship and the asteroid decreases player ship's life")
{
    playerShip playerShip_; 
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 

    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(playerShip_.getPos());

    asteroids asteroids_;
    asteroids_.addEnemy(enemy_);

    playerLives playerLives_;
    playerLives_.resetplayerLives();
    auto initialLives_ = 3;
    asteroids_.checkPlayerCollision(playerShip_);
    CHECK(playerLives_.getplayerLives() == initialLives_ - 3); // all lives are expected to be lost
}

// // ------------- Tests for Humanoid Class ----------------

TEST_CASE("Lander is able to capture humanoid")
{
    alien testEnemy_;
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids handlingHumanoids_; 
    handlingHumanoids_.addHumanoid(humanoid_);
    auto initialPos = handlingHumanoids_.humanoidsPositions();
    std::vector<projectiles> temp; 
    playerShip playerShip_; 
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    handlingHumanoids_.checkCollisions(testEnemy_,temp,playerShip_);
    //Checking lander transfered to humanoids aliens 
    CHECK(testEnemy_.getEnemySprites().size() == 0);
    CHECK(initialPos[0].x != handlingHumanoids_.humanoidsPositions()[0].x);
    CHECK(initialPos[0].y != handlingHumanoids_.humanoidsPositions()[0].y);
    CHECK(handlingHumanoids_.getNumberCapturedHumanoids() == 1);
}

TEST_CASE("Humanoid captured by lander moves up")
{
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.01f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    std::vector<projectiles> playerProjectiles; 
    playerShip playerShip_;
    human.checkCollisions(testEnemy_,playerProjectiles,playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    sf::Vector2f intialHumanPos = human.humanoidsPositions()[0];
    human.update();
    CHECK(intialHumanPos.x == human.humanoidsPositions()[0].x); 
    CHECK(intialHumanPos.y != human.humanoidsPositions()[0].y);
}

TEST_CASE("Humanoid can be freed from lander with player projectile collision after being captured")
{
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.01f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-lander.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    playerShip playerShip_;
    PlayerProjectiles PlayerProjectiles_; 
    human.checkCollisions(testEnemy_,PlayerProjectiles_.getPlayerProjectiles(),playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    sf::Vector2f intialHumanPos = human.humanoidsPositions()[0];
    human.update();
    std::vector<projectiles> projectiles_; 
    sf::Texture projectile_texture;
    projectile_texture.loadFromFile("resources/shoot.png");
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,testEnemy_.getEnemySprites()[0].getPosition()));
    human.checkCollisions(testEnemy_,projectiles_,playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 0);
    CHECK(human.getNumberOfFallingHumanoids() == 1);
}

TEST_CASE("After humanoid is freed from capture it will move down")
{
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.01f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-lander.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    std::vector<projectiles> projectiles_; 
    playerShip playerShip_;
    //Captured humanoid
    human.checkCollisions(testEnemy_,projectiles_,playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    human.update();
    sf::Texture projectile_texture;
    projectile_texture.loadFromFile("resources/shoot.png");
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,testEnemy_.getEnemySprites()[0].getPosition()));
    //Free humanoid
    human.checkCollisions(testEnemy_,projectiles_,playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 0);
    CHECK(human.getNumberOfFallingHumanoids() == 1); 
    sf::Vector2f intialHumanPos = human.humanoidsPositions()[0];
    //Allow to fall
    human.update();
    CHECK(intialHumanPos.x == human.humanoidsPositions()[0].x);
    CHECK(intialHumanPos.y != human.humanoidsPositions()[0].y);
}

TEST_CASE("Player ship is able to catch falling humanoid")
{
    //Intial capture and release of humanoid 
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.01f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(1470.0f,310.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(1470.0f,310.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    std::vector<projectiles> projectiles_; 
    playerShip playerShip_; 
    human.checkCollisions(testEnemy_,projectiles_,playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    sf::Texture projectile_texture;
    projectile_texture.loadFromFile("resources/shoot.png");
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,testEnemy_.getEnemySprites()[0].getPosition()));
    human.checkCollisions(testEnemy_,projectiles_,playerShip_); 
    //Will be -1 when there is no humanoid caught
    CHECK(human.getNumberOfCaughtHumanoids() != -1); 

    //Check number of falling humanoids have decreased so player has caught it
    CHECK(human.getNumberOfFallingHumanoids() == 0);
}

TEST_CASE("Check player ship is able to move with caught humanoid")
{
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.01f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(1470.0f,310.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(1470.0f,310.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    std::vector<projectiles> projectiles_; 
    playerShip playerShip_;
    playerShip_.setdt(0.01f);
    human.checkCollisions(testEnemy_,projectiles_,playerShip_);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    sf::Texture projectile_texture;
    projectile_texture.loadFromFile("resources/shoot.png");
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,testEnemy_.getEnemySprites()[0].getPosition()));
    human.checkCollisions(testEnemy_,projectiles_,playerShip_); 
    //Will be -1 when there is no humanoid caught
    CHECK(human.getNumberOfCaughtHumanoids() != -1); 

    //Check number of falling humanoids have decreased so player has caught it
    CHECK(human.getNumberOfFallingHumanoids() == 0);
    //Check humanoid is actually caught 

    playerShip_.processEvent(sf::Keyboard::A,true);
    auto initialHumanPos = human.humanoidsPositions()[0];
    playerShip_.update();
    //Required to update the positions of the playership
    human.checkCollisions(testEnemy_,projectiles_,playerShip_); 
    human.update();

    CHECK(human.humanoidsPositions()[0].x == playerShip_.getPos().x);
    CHECK(human.humanoidsPositions()[0].y == playerShip_.getPos().y);
}

TEST_CASE("Check lander above humanoid tracks humanoid")
{
    alien testEnemy_;
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,600.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    std::vector<projectiles> projectiles; 
    playerShip playerShip; 
    human.checkCollisions(testEnemy_,projectiles,playerShip);
    CHECK(human.getNumberOfTrackingAliens() == 1);
    CHECK(human.getNumberOfTrackingHumanoids() == 1);
}

TEST_CASE("Check tracking humanoid is captured")
{
    alien testEnemy_;
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,600.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    std::vector<projectiles> projectiles_; 
    playerShip playerShip; 
    human.checkCollisions(testEnemy_,projectiles_,playerShip);
    CHECK(human.getNumberOfTrackingAliens() == 1);
    while(human.getNumberOfTrackingHumanoids() == 1)
    {
        human.update();
        human.checkCollisions(testEnemy_,projectiles_,playerShip);
    }
    CHECK(human.getNumberCapturedHumanoids() == 1);
    CHECK(human.getNumberOfTrackingHumanoids() == 0);

}

TEST_CASE("Check falling humanoid eliminated when hitting the ground")
{
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.1f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-lander.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    playerShip playerShip;
    PlayerProjectiles PlayerProjectiles_;
    human.checkCollisions(testEnemy_,PlayerProjectiles_.getPlayerProjectiles(),playerShip);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    sf::Vector2f intialHumanPos = human.humanoidsPositions()[0];
    human.update();
    std::vector<projectiles> projectiles_; 
    sf::Texture projectile_texture;
    projectile_texture.loadFromFile("resources/shoot.png");
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,testEnemy_.getEnemySprites()[0].getPosition()));
    human.checkCollisions(testEnemy_,projectiles_,playerShip);
    while(human.humanoidsPositions()[0].y < 750.0f)
    {
        human.update();
    }
    human.checkCollisions(testEnemy_,projectiles_,playerShip);
    //Check humanoid is deleted when hitting the ground
    CHECK(human.humanoidsPositions().size() == 0);
}

TEST_CASE("Check falling humanoid can be shot by players projectiles")
{
    alien testEnemy_;
    testEnemy_.setDeltaTime(0.1f);
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-lander.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids human; 
    human.setDeltaTme(0.01f);
    human.addHumanoid(humanoid_);
    playerShip playerShip;
    PlayerProjectiles PlayerProjectiles_;
    human.checkCollisions(testEnemy_,PlayerProjectiles_.getPlayerProjectiles(),playerShip);
    CHECK(human.getNumberCapturedHumanoids() == 1);
    sf::Vector2f intialHumanPos = human.humanoidsPositions()[0];
    human.update();
    std::vector<projectiles> projectiles_; 
    sf::Texture projectile_texture;
    projectile_texture.loadFromFile("resources/shoot.png");
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,testEnemy_.getEnemySprites()[0].getPosition()));
    human.checkCollisions(testEnemy_,projectiles_,playerShip);
    projectiles_.push_back(projectiles(projectile_texture,{0.0f,0.0f},0.0f,human.humanoidsPositions()[0]));
    human.checkCollisions(testEnemy_,projectiles_,playerShip);
    CHECK(human.humanoidsPositions().size() == 0);
}

TEST_CASE("Check captured humanoid eliminated when hitting top of game screen")
{
    alien testEnemy_;
    sf::Sprite enemy_; 
    sf::Texture enemyTexture_; 
    enemyTexture_.loadFromFile("resources/enemy-pod.png");
    enemy_.setTexture(enemyTexture_);
    enemy_.setScale(1.0f,1.0f);
    enemy_.setPosition(300.0f,300.0f);
    testEnemy_.addEnemy(enemy_);
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    sf::Sprite humanoid_; 
    sf::Texture humanoidTexture; 
    humanoidTexture.loadFromFile("resources/humanoid.png");
    humanoid_.setTexture(humanoidTexture);
    humanoid_.setScale(1.0f,1.0f);
    humanoid_.setPosition(300.0f,300.0f);
    handlingHumanoids handlingHumanoids_; 
    handlingHumanoids_.addHumanoid(humanoid_);
    handlingHumanoids_.setDeltaTme(0.01f);
    auto initialPos = handlingHumanoids_.humanoidsPositions();
    std::vector<projectiles> temp; 
    playerShip playerShip; 
    CHECK(testEnemy_.getEnemySprites().size() == 1);
    handlingHumanoids_.checkCollisions(testEnemy_,temp,playerShip);
    while(handlingHumanoids_.humanoidsPositions()[0].y > 750.0f*0.17f)
    {
        handlingHumanoids_.update();
    }  
    handlingHumanoids_.checkCollisions(testEnemy_,temp,playerShip);
    CHECK(handlingHumanoids_.humanoidsPositions().size() == 0);
}

// // ------------- Tests for Scrolling Class ----------------

// //Tests for minimap would be the same as gameView since its the same view just centered at entire screen

TEST_CASE("Player moving right keeps game viewport centered at players position")
{
    playerShip playership; 
    playership.setdt(0.05f);
    scrolling scroll; 
    sf::RenderWindow window; 
    window.setSize({1350,750});
    scroll.setScrolling(window);
    scroll.setviewgameView(window,playership.getPos());
    sf::Vector2f initialPos = scroll.getgameView().getViewport().getPosition();
    playership.processEvent(sf::Keyboard::D,true);
    playership.update();
    playership.update();
    CHECK(scroll.getgameView().getViewport().getPosition().x == initialPos.x);
}

TEST_CASE("Player moving left keeps game viewport centered at players position")
{
    playerShip playership; 
    playership.setdt(0.05f);
    scrolling scroll; 
    sf::RenderWindow window; 
    window.setSize({1350,750});
    scroll.setScrolling(window);
    scroll.setviewgameView(window,playership.getPos());
    sf::Vector2f initialPos = scroll.getgameView().getViewport().getPosition();
    playership.processEvent(sf::Keyboard::A,true);
    playership.update();
    playership.update();
    CHECK(scroll.getgameView().getViewport().getPosition().x == initialPos.x);
}

TEST_CASE("Outline of player moves with it")
{
    playerShip playership; 
    playership.setdt(0.05f);
    scrolling scroll; 
    sf::RenderWindow window; 
    window.setSize({1350,750});
    scroll.setScrolling(window);
    scroll.setPlayerBorders(playership.getPos());
    auto intialPos = scroll.LeftBorder();
    playership.processEvent(sf::Keyboard::D,true);
    playership.update();
    scroll.setPlayerBorders(playership.getPos());
    CHECK(intialPos.getPosition().x != scroll.LeftBorder().getPosition().x);
}

// // ------------- Tests for Scoring Class ----------------

TEST_CASE("Score increases by set amount")
{
    score points; 
    points.resetScore();
    int point = 100; 
    points.updateScore(point);
    CHECK(points.getScore() == point);
}

TEST_CASE("Scoring vector is populated correctly")
{
    score score_; 
    auto points_ = 100; 

    score_.resetScore();
    score_.updateScore(points_);
    CHECK(score_.getScore() == points_);

    score_.updateHighScore();
    points_ = 150; 
    score_.updateScore(points_);
    score_.updateHighScore();

    CHECK(score_.getHighScores().size() == 2);
}