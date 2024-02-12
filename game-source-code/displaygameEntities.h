#ifndef DISPLAYGAMEENTITIES_H
#define DISPLAYGAMEENTITIES_H

/**
 * @file displaygameEntities.h
 * @brief This class is responsible for displaying all game entities within respective views of the game window.
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include "playerShip.h"
#include "pod.h"
#include "alien.h"
#include "asteroids.h"
#include "score.h"
#include "scrolling.h"
#include "playerShield.h"
#include "handlingHumanoids.h"
#include "playerLives.h"
#include "PlayerProjectiles.h"
#include "fuel.h"
#include <iostream>

class displaygameEntities
{
    public: 
    /**
     * @brief Construct a new displaygame Entities object and intializes background texture.
     * 
     */
    displaygameEntities();
    /**
     * @brief Destroy the displaygame Entities object
     * 
     */
    ~displaygameEntities();
    /**
     * @brief Returns vector of sf::RectangleShape objects initialized by scrolling class for players visible space.
     * 
     * @return std::vector<sf::RectangleShape> vector of sf::Rectangle shape objects representing players visible space.
     */
    std::vector<sf::RectangleShape> getborder();
    /**
     * @brief Displays corresponding game entities within respective views such as infoView, minimapView, gameView and wrappingViews. 
     * 
     * @param window Reference to sf::RenderWindow object. 
     * @param playership object of playerShip class. 
     * @param aliens_ object of alien class.
     * @param pod_ object of pod class. 
     * @param asteroids_ object of asteriods class.
     * @param playerScore_ object of score class. 
     * @param human_ object of handlingHumanoids class.
     * @param playerShield_ object of playerShield class.
     * @param playerLives_ object of playerLives class.
     * @param playerProjectiles_ object of playerProjectiles class.
     * @param playerFuel_ object of fuel class.
     */
    void display(sf::RenderWindow& window, playerShip& playership, alien& aliens_
    ,pod& pod_,asteroids& asteroids_,score& playerScore_,handlingHumanoids& human_,
    playerShield& playerShield_, playerLives& playerLives_,  PlayerProjectiles& playerProjectiles_,
    fuel& playerFuel_);
    private:
    void initializeInforViewBorder(sf::RenderWindow& window);
    void displayInfoView(sf::RenderWindow& window,score& playerScore_,fuel& playerFuel_,playerLives& playerLives_,playerShield& playerShield_);
    void displayGameView(sf::RenderWindow& window,playerShip& playership, alien& aliens_
    ,pod& pod_,asteroids& asteroids_,handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_);
    void displayMiniMap(sf::RenderWindow& window,playerShip& playership, alien& aliens_
    ,pod& pod_,asteroids& asteroids_,handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_);
    void displayWrapping(sf::RenderWindow& window,playerShip& playership, alien& aliens_
    ,pod& pod_,asteroids& asteroids_,handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_);
    void displayGameEntities(sf::RenderWindow &window, playerShip& playership, alien& aliens_
    ,pod& pod_,asteroids& asteroids_,handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_);

    //Scrolling class
    scrolling screen;

    //Background 
    sf::Texture background_texture_;
    sf::Sprite  background_sprite_; 
    sf::Color darkBlue = sf::Color(0,0,51);
};

#endif