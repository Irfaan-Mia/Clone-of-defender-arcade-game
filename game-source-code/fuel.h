#ifndef  FUEL_H
#define  FUEL_H

/**
 * @file fuel.h
 * @brief This class is responsible for spawning, displaying and handling the events of the players fuel.  
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath> 
#include <vector> 
#include <string>
#include <iostream>

class fuel
{
    public: 
    
    /** \brief Constructor

        Initiaizes textures and fuel gauge size.

    */
    fuel();
    
    /** \brief Deconstructor

        Deletes object created by constructor.

    */
    ~fuel();

    /** \brief Spawns fuel 

        Spawns fuel in a random x axis position within game screen. 

    */
    void spawnFuel();

    /** \brief Check player collision with fuel.  

        Checks if player has a collision with fuel. if collision increases total fuel amount.

    \param playerPos sf::FloatRect containing x and y coordinates of player ship.
    */
    void checkcollisionwithFuel(sf::FloatRect playerPos);
    
    /** \brief Checks if player has fuel.

        Checks if the player has fuel remaining.

    \return Returns true if player has fuel. otherwise false.
    */
    bool doesplayerhaveFuel();

    /** \brief Decreases fuel.

        Decreases remaining fuel when timer condition is met.

    */
    void decreasefuel();

    /** \brief Adds fuel sprite.

        Adds fuel sprite to vector containing all fuel canisters.

    \param fuel sf::Sprite object representing fuel canister.
    */
    void addfuel(sf::Sprite fuel);

    /** \brief Decreases fuel.

        decreases remaining fuel by a fixed amount.

    */
    void decrementfuel(); 

    /** \brief Displays fuel.

        Displays fuel within the game screen.

    \param window Reference to sf::RenderWindow object. 
    */
    void displayFuel(sf::RenderWindow& window);

    /** \brief Checks if new fuel canister overlaps.

        Checks if the new fuel canister being spawned overlaps with existing fuel canister.

    \param test sf::Sprite object of new fuel canister that needs to be spawned.
    \param randX_ float value of x position of new fuel canister.
    \param randY_ float value of y position of new fuel canister.
    */
    bool checkfuelOverlap(sf::Sprite test,float randX_, float randY_);

    /** \brief Updates fuel gauage.

        Updates fuel gauage to current fuel amount of player.

    */
    void updatefuelGauge();
    
    /** \brief Display fuel gauage.

        Displays fuel gauge in specified position.

    \param window Reference to sf::RenderWindow object. 
    */
    void displayfuelGauge(sf::RenderWindow& window);

    /** \brief Returns crashing speed.

        returns speed that player will crash when out of fuel.

    \return sf::Vector2f containing x and y speed for players crashing speed.
    */
    sf::Vector2f getcrashingSpeed();

    /** \brief resets fuel.

        Resets to fuel to initial state.

    */
    void resetFuel(); 

    /** \brief Returns fuel objects.

        Returns fuel canister currently within the game screen.

    \return Returns vector of sprite objects representing the fuel canisters within game screen.
    */
    std::vector<sf::Sprite> getfuel();

    /** \brief Returns total fuel.

        Returns current total of fuel player has. 

    \return integer value of remaining fuel value from 0 to 100.
    */
    int gettotalFuel();

    private:
    std::vector<sf::Sprite> Fuel_; 
    sf::Texture fuel_texture; 
    static int totalFuel_;
    int fuelCount_ = 0;
    int fuelConsumption = 5;
    int fuelconsumptionInterval = 5000;
    int fuelspawnInterval = 1000;
    int fueldespawnInterval = 5000;
    const int maxFuel_ = 2; 
    sf::Vector2f crashingSpeed_{0.0f,5000.0f};
    sf::RectangleShape playerfuelBar_; 
    sf::RectangleShape playerfuelBarInverted_; 
    sf::RectangleShape playerfuelbarBack_;
    sf::Text textfuelPercentage; 
    sf::Font font; 

     sf::Vector2f maxscreenSize{3000.0f - 50.0f,750.0f - 30.0f};

};

#endif 