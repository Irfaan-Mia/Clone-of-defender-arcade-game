#ifndef SCROLLING_H
#define SCROLLING_H

/**
 * @file scrolling.h
 * @brief This class is responsible for setting the main render window to specific views such as infoView, gameView, miniMap and WrappingView. The class 
    is responsible for setting reference window to each specific reference views. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <SFML/Graphics.hpp>
#include <iostream>
#include "projectiles.h"

class scrolling
{
    public:
    /** \brief Constructor 

        Intializes sizes of left and right border objects representing players visible range. 

    */ 
    scrolling();

    /** \brief Initializes sizes of views.

        Initializes sizes of views based on window size.

    \param window Reference to sf::RenderWindow object. 
    */
    void setScrolling(sf::RenderWindow& window);

    /** \brief Sets window to game view.

        Sets the window to specific game view and moves view based on players position.

    \param window Reference to sf::RenderWindow object. 
    \param playerPos sf::Vector2f representing x and y position of the player.
    */
    void setviewgameView(sf::RenderWindow& window, sf::Vector2f playerPos);

    /** \brief Sets window to info view.

        Sets the window to specific info view for minimap and other extras to be displayed on.

    \param window Reference to sf::RenderWindow object. 
    */
    void setviewinfoView(sf::RenderWindow& window); 

    /** \brief Sets window to minimap view.

        Sets the window to minimap view to display objects on the minimap.

    \param window Reference to sf::RenderWindow object. 
    */
    void setviewminimapView(sf::RenderWindow& window);

    /** \brief Updates player borders to new player position.

        Sets the outline of the players visible range in minimap to new player position.

    \param playerPos sf::Vector2f representing x and y coordinates of player 
    */
    void setPlayerBorders(sf::Vector2f playerPos);

    /** \brief Draws border of players visible range.

        Draws maximum visible range that player is able to see in game screen.

    \param window Reference to sf::RenderWindow object. 
    */
    void drawPlayerBorders(sf::RenderWindow& window);
    
    /** \brief Returns game view.

        Returns the game view with specified information.

    \return sf::View object used for game screen
    */
    sf::View& getgameView();

    /** \brief Returns object representing player left border.

        Returns the sf::RectangleShape object used to show left border of players visible range based on players position.

    \return sf::RectangleShape object representing players left border. 
    */
    const sf::RectangleShape& LeftBorder();
    /** \brief Returns object representing players right border.

        Returns the sf::RectangleShape object used to show right border of players visible range based on players position.

    \return sf::RectangleShape object representing players right border. 
    */
    const sf::RectangleShape& RightBorder();
    /**
     * @brief Specific view for extending screen required for wrapping is set
     * 
     * @param window Reference to sf::RenderWindow object. 
     * @param playerPos sf::Vector2f representing x and y coordinates of the player. 
     * @return true if the view is set.
     * @return false if the view is not set.
     */
    bool isWrappingViewSet(sf::RenderWindow& window, sf::Vector2f playerPos);

    private: 
    sf::RectangleShape LeftBorder_, RightBorder_;
    float maxgameView_{3000.0f}; 
    sf::View gameView_;
    sf::View infoView_; 
    sf::View miniMap_; 
    sf::View rightView_; 
    sf::View leftView_; 
    sf::Vector2f playerPos; 
};

#endif
