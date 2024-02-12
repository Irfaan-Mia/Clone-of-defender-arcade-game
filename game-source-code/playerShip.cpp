#include "playerShip.h"
#include "playerShield.h"
#include <iostream> 

playerShip::playerShip()
{
    if(!ship_left_texture.loadFromFile("resources/ship_left.png"))
    {
        std::cerr << "ERROR::LOADING SHIP_LEFT TEXTURE" << std::endl;
        return;
    }
    if(!ship_right_texture.loadFromFile("resources/ship_right.png"))
    {
        std::cerr << "ERROR::LOADING SHIP_RIGHT TEXTURE" << std::endl;
        return;
    }

    if(!collisionSoundBuffer_.loadFromFile("resources/ship-collision.wav"))
    {
        std::cerr << "ERROR::LOADING SHIP COLLISION SOUND" << std::endl;
        return;
    }
    if (!continuousMovementSoundBuffer_.loadFromFile("resources/ship-movement.wav")) {
    std::cerr << "ERROR::LOADING SHIP MOVEMENT SOUND" << std::endl;
    return;
    }
    if(!ship_left_shield_texture.loadFromFile("resources/ship_left_shield.png"))
    {
        std::cerr << "ERROR::LOADING SHIP_LEFT_SHIELD TEXTURE" << std::endl;
        return; 
    }
    if(!ship_right_shield_texture.loadFromFile("resources/ship_right_shield.png"))
    {
        std::cerr << "ERROR::LOADING SHIP_RIGHT_SHIELD TEXTURE" << std::endl;
        return; 
    }
    
    const sf::Vector2u windowSize(1350, 750);
    float topLeftX = 10.0f; 
    float topLeftY = static_cast<float>(windowSize.y) * 0.05f; 

    playership.setTexture(ship_left_texture);
    playership.setScale(player_scale);
    playership.setPosition(sf::Vector2f(maxscreenSize.x/2.0f,maxscreenSize.y/2.0f));
    collisionSound_.setBuffer(collisionSoundBuffer_);
    collisionSound_.setVolume(10);
    continuousMovementSound_.setBuffer(continuousMovementSoundBuffer_);
    continuousMovementSound_.setVolume(5); // Adjust the volume as needed
}

playerShip::~playerShip()
{
}

const sf::Vector2f &playerShip::getPos() const
{
    return playership.getPosition();
}


void playerShip::processEvent(sf::Keyboard::Key keypressed,bool isKeyPressed)
{
    sf::Vector2f direction; 
        if(isKeyPressed)
        {
           keyPressed(keypressed);
        }
        else if(!isKeyPressed)
        { 
           keyReleased(keypressed);
        }
}


void playerShip::update()
{

    //Swap textures for player 
    switchingplayerTexture();

    movePlayer();
}


void playerShip::drawto(sf::RenderTarget& window)
{
    window.draw(playership);
}

void playerShip::resetPlayerShip()
{
    playership.setTexture(ship_left_texture);
    playership.setScale(player_scale);
    playership.setPosition(sf::Vector2f(maxscreenSize.x/2.0f,maxscreenSize.y/2.0f));
    Fuel_.resetFuel();
    score_.resetScore();
    isRighttexture = false; 
    up = false; 
    right = false; 
    left = false; 
    down = false;

    //Ending game
    GameOver = false; 
    Win = false; 
}

sf::Vector2f playerShip::getmovementSpeed()
{
    return movementspeed;
}

void playerShip::switchingplayerTexture()
{
    //Check if player activated shield 
    if(playerShield::isshieldActive() && isRighttexture)
    {
        playership.setTexture(ship_right_shield_texture); 
    }
    else if(playerShield::isshieldActive() && !isRighttexture)
    {
        playership.setTexture(ship_left_shield_texture);
    }
    else if(isRighttexture)
    {
        playership.setTexture(ship_right_texture);
    }
    else
    {
        playership.setTexture(ship_left_texture);
    }
}

bool playerShip::isGameOver()
{
    return GameOver;
}

sf::FloatRect playerShip::getplayerGlobalsBounds()
{
    return playership.getGlobalBounds();
}

void playerShip::setdt(float deltaTime)
{
    dt = deltaTime;
}

sf::Vector2f playerShip::getPlayerDirection()
{
   if(isRighttexture)
   {
    return {1.0f,0.0f};
   }
   else
   {
    return {-1.0f,0.0f};
   }
}

void playerShip::keyPressed(sf::Keyboard::Key keypressed)
{
    switch (keypressed)
    {
    case sf::Keyboard::W:
        up = true;
        break;
    case sf::Keyboard::A:
        left = true;
        isRighttexture = false; 
        break;
    case sf::Keyboard::S:
        down = true; 
        break; 
    case sf::Keyboard::D:
        right = true;
        isRighttexture = true; 
        break; 
    default: 
    //Invalid key so no action required
        break;
    }      
}

void playerShip::keyReleased(sf::Keyboard::Key keypressed)
{
switch (keypressed)
    {
    case sf::Keyboard::W:
        up = false;
        break;
    case sf::Keyboard::A:
        left = false;
        break;
    case sf::Keyboard::S:
        down = false; 
        break; 
    case sf::Keyboard::D:
        right = false;
        break; 
    default: 
    //Invalid key so no action required
        break;
    }
}

void playerShip::movePlayer()
{
    //Handle movement
    sf::Vector2f movement;
    if(Fuel_.doesplayerhaveFuel())
    {
        playerhasFuel(movement);
    }
    else
    {
        movement = Fuel_.getcrashingSpeed();
        movement = movement*dt;
    }
    wrappingPlayer(movement);
   
    playership.move(movement);
    if(movement == Fuel_.getcrashingSpeed()*dt && playership.getPosition().y > maxscreenSize.y)
    {
        GameOver = true; 
        Win = false; 
    }
}

void playerShip::playerhasFuel(sf::Vector2f& movement)
{
    //Check combinations before singular events 
        if(down == true && left == true)
        {
            movement.x -= movementspeed.x*sin(45*pi/180); 
            movement.y += movementspeed.y*cos(45*pi/180); 
            Fuel_.decreasefuel();
        }
        else if(down == true && right == true)
        {
            movement.x += movementspeed.x*sin(45*pi/180); 
            movement.y += movementspeed.y*cos(45*pi/180);
            Fuel_.decreasefuel();
        }
        else if(up == true && left == true)
        {
            movement.x -= movementspeed.x*sin(45*pi/180); 
            movement.y -= movementspeed.y*cos(45*pi/180);
            Fuel_.decreasefuel();
        }
        else if(up == true && right == true)
        {
            movement.x += movementspeed.x*sin(45*pi/180); 
            movement.y -= movementspeed.y*cos(45*pi/180);
            Fuel_.decreasefuel();
        }
        else if(up)
        {
            movement.y -= movementspeed.y;
            Fuel_.decreasefuel();
        }
        else if(down)
        {
            movement.y += movementspeed.y; 
            Fuel_.decreasefuel();
        }
        else if(left)
        {
            movement.x -= movementspeed.x;
            Fuel_.decreasefuel();
        }
        else if(right)
        {
            movement.x += movementspeed.x; 
            Fuel_.decreasefuel();
        }
        movement = movement*dt; 
}

void playerShip::wrappingPlayer(sf::Vector2f& movement)
{
     //     //Temporary boundary for player movement//
    if(playership.getPosition().x + movement.x < 0 && left)
    {
        playership.setPosition(3000.0f,playership.getPosition().y);
    }
    else if(playership.getPosition().x + movement.x > maxscreenSize.x && right)
    {
        playership.setPosition(playerTeleportationOffset,playership.getPosition().y);
    }
    else if(playership.getPosition().y + movement.y < (maxscreenSize.y * 0.18) && up)
    {
        movement.y = 0.0f; 
    }
    else if(playership.getPosition().y + movement.y > maxscreenSize.y && down)
    {
        movement.y = 0.0f; 
    }
}
