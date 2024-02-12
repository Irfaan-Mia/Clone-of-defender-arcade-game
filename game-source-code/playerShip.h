#ifndef PLAYERSSHIP_H
#define PLAYERSSHIP_H

/** \file player_ship.h
    \brief Contains code for managing players ship 
*/

/* Header Files */
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio.hpp>
#include "enemies.h"
#include "score.h"
#include "fuel.h"
#include <cmath> 
#include <vector> 
#include <string>

class playerShip
{
    public:
    /** \brief Constructor

    Creates a ship object and initializes some private variables 
    */ 
    playerShip();

    /** \brief Destructor

     Destroys a ship object.
    */
    ~playerShip();

    /** \brief Returns position of the ship 

        Returns current position of the ship within the screen 

    \return Returns and x and y coordinates of players ship
    */
    const sf::Vector2f& getPos() const; 

    /** \brief Processes input from player

        Control private variables based on the input received from the player

    \param keypressed input code of specific key on the keyboard pressed 
    \param isKeyPressed true or false based on if the key on the keyboard is pressed or released respectively
    */
    void processEvent(sf::Keyboard::Key keypressed,bool isKeyPressed);

    /** \brief Update player ship position

     Updates the ships current position to new position based on users input
    */
    void update();

    /** \brief Displays the current ship and position

        Displays the current position of the ship based on players inputs 

     \param window Reference to sf::RenderWindow object.
    */
    void drawto(sf::RenderTarget& window);

    /** \brief Resets players ship to initial values

        Resets the players ship to intial values so a new game can be started 

    */
    void resetPlayerShip();

    /** \brief Returns players movement speed

        Returns the current players movement speed 

    */
    sf::Vector2f getmovementSpeed();
    /** \brief Swtiches players texture

        Switches players texture based on if shield is activated or not 

    */
   void switchingplayerTexture();

    /**
     * @brief Checks if the player is still alive.
     * 
     * @return true if the player has been eliminated.
     * @return false if the player is still alive.
     */
    bool isGameOver();



    /** \brief Returns players coordinates 

        Returns players x and y coordinates within game screen  

    \return Returns x and y coordinate of player  
    */
    sf::FloatRect getplayerGlobalsBounds();

    /** \brief Sets delta time 

        Sets delta time used in movement so independent of frame rate  

    \param deltaTime Change in time 
    */
    void setdt(float deltaTime);

    /**
     * @brief Get the Player Direction
     * 
     * @return sf::Vector2f x coordinate is positive for right and negative for left
     */
    sf::Vector2f getPlayerDirection();
    
    private:
    void keyPressed(sf::Keyboard::Key keypressed);
    void keyReleased(sf::Keyboard::Key keypressed);
    void movePlayer();
    void playerhasFuel(sf::Vector2f& movement);
    void wrappingPlayer(sf::Vector2f& movement);

    //Ships texture
    score score_;
    sf::Sprite playership;
     
    //Ships projectiles 
    sf::Sound collisionSound_; 
    sf::SoundBuffer collisionSoundBuffer_; 
    sf::SoundBuffer continuousMovementSoundBuffer_;
    sf::Sound continuousMovementSound_;


    //Ships variables
    sf::Texture ship_left_texture; 
    sf::Texture ship_right_texture;
    sf::Texture ship_left_shield_texture; 
    sf::Texture ship_right_shield_texture; 
    sf::Vector2f maxscreenSize{3000.0f - 50.0f,750.0f - 30.0f};
    sf::Vector2f movementspeed{400.0f,400.0f}; 
    sf::Vector2f player_scale{1.0f,1.0f};
    const float pi = 3.14159; 
    
    //Players Wrapping offset 
    float playerTeleportationOffset = -40.0f;

    //Players fuel 
    fuel Fuel_; 

    //Movement of ship
    bool isRighttexture = false; 
    bool up = false; 
    bool right = false; 
    bool left = false; 
    bool down = false;

    //Ending game
    bool GameOver = false; 
    bool Win = false; 

    //Frame rate control
    float dt; 
};

#endif 
