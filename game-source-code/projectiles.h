#ifndef PROJECTILES_H
#define PROJECTILES_H

/** \file projectiles.h
    \brief Contains code for managing projectiles from either enemies or players ship 
*/

/* Header Files */
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class projectiles
{
public: 
    /** \brief Constructor 

        Creates a projectile object and initializes private variables using parameters 

     \param projectile_texture The texture that will be used for the projectile
     \param direction   The direction the projectile with move within the screen
     \param movementspeed The speed at which the projectile will move 
     \param starting_pos The position the projectile will start within the screen
    */
    projectiles(sf::Texture& projectiles_texture,sf::Vector2f direction,float movementspeed,sf::Vector2f starting_pos);
    /** \brief Destructor

     Destroys a projectiles object.
    */
    ~projectiles();

    /** \brief Update projectiles

     Updates the projectiles current position to new position
    */
    void update();

    /** \brief Displays the projectile

        Displays the current position of the projectile based on inputs received in the constructor 

     \param window Reference to sf::RenderWindow object.
    */
    void drawto(sf::RenderTarget& window); 

    /** \brief Returns projectile sprite object

     Returns sprite object of specific projectile

     \return Returns sprite object of specific projectile
    */
    sf::Sprite& getSprite(); 

    /** \brief Returns projectiles current position

     Returns the current position of the projectile within the screen

     \return Returns projectile x and y position
    */
    sf::Vector2f get_projectile_position(); 
    /**
     * @brief Sets delta time required for movement
     * 
     * @param deltaTime float value for change in time 
     */
    void setdt(float deltaTime);
private:
    sf::Sprite projectile_shape_; 
    sf::Vector2f direction_;
    float movementspeed_;
    sf::Vector2f starting_position_;
    sf::Vector2f projectile_scale{0.5f,0.5f};
    float dt_; 
};
#endif