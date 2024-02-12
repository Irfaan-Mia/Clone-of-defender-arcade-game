/** \file displayGameEntities.cpp
*/

/* Header Files */
#include "displayGameEntities.h"

displaygameEntities::displaygameEntities()
{
    if(!background_texture_.loadFromFile("resources/ground.png"))
    {
        return; 
    }
    background_texture_.setRepeated(true);
    background_sprite_.setTexture(background_texture_);
    background_sprite_.setPosition(0.0f,100.0f);
    background_sprite_.setScale(3000.0f/1350.0f,750.0f/1110.0f);
}

displaygameEntities::~displaygameEntities()
{
}

std::vector<sf::RectangleShape> displaygameEntities::getborder()
{
    std::vector<sf::RectangleShape> temp{screen.LeftBorder(),screen.RightBorder()};
    return temp; 
}

void displaygameEntities::display(sf::RenderWindow& window, playerShip& playership, alien& aliens_
    ,pod& pod_,asteroids& asteroids_,score& playerScore_,handlingHumanoids& human_,
    playerShield& playerShield_, playerLives& playerLives_,  PlayerProjectiles& playerProjectiles_,
    fuel& playerFuel_)
{
    window.clear(darkBlue);
    screen.setScrolling(window);
    displayInfoView(window,playerScore_,playerFuel_,playerLives_,playerShield_);
    displayGameView(window, playership,  aliens_, pod_, asteroids_,human_,  playerProjectiles_, playerFuel_);
    displayMiniMap(window,playership,  aliens_, pod_, asteroids_,human_,  playerProjectiles_, playerFuel_);
    displayWrapping(window,playership,  aliens_, pod_, asteroids_,human_,  playerProjectiles_, playerFuel_);
}

void displaygameEntities::initializeInforViewBorder(sf::RenderWindow &window)
{
    // Spawn Horizontal Border
    auto lineWidth_ = 2;
    sf::RectangleShape horizontalLine_;
    horizontalLine_.setSize(sf::Vector2f(window.getSize().x, lineWidth_));
    horizontalLine_.setPosition(0, window.getSize().y * 0.17);
    horizontalLine_.setFillColor(sf::Color::Yellow);
    float bottomBorder_ = horizontalLine_.getPosition().y; 
    
    // Spawn Vertical Borders
    sf::RectangleShape line1_, line2_;
    line1_.setSize(sf::Vector2f(lineWidth_, bottomBorder_)); 
    line1_.setPosition(window.getSize().x * 0.30, 0); 
    line1_.setFillColor(sf::Color::Yellow);

    line2_.setSize(sf::Vector2f(lineWidth_, bottomBorder_)); 
    line2_.setPosition(window.getSize().x * 0.70, 0); 
    line2_.setFillColor(sf::Color::Yellow);

    //Set view to draw info bar 
    screen.setviewinfoView(window);

    // Draw Lines
    window.draw(line1_); 
    window.draw(line2_); 
    window.draw(horizontalLine_);
}

void displaygameEntities::displayInfoView(sf::RenderWindow &window, score &playerScore_, fuel &playerFuel_, playerLives &playerLives_, playerShield &playerShield_)
{
    //Info view display border
    initializeInforViewBorder(window);

    // Player Score
    playerScore_.displayScore(window);

    //PLayer lives and fuel
    playerFuel_.displayfuelGauge(window);
    playerLives_.displayLives(window);
    playerShield_.drawshieldIcon(window);
}

void displaygameEntities::displayGameView(sf::RenderWindow& window,playerShip& playership, alien& aliens_,pod& pod_,asteroids& asteroids_,
handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_)
{
    screen.setviewgameView(window,playership.getPos());
    displayGameEntities(window, playership, aliens_, pod_, asteroids_, human_, playerProjectiles_, playerFuel_);
}

void displaygameEntities::displayMiniMap(sf::RenderWindow& window,playerShip& playership, alien& aliens_,pod& pod_,asteroids& asteroids_,
handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_)
{
    screen.setviewminimapView(window);
    screen.setPlayerBorders(playership.getPos());
    screen.drawPlayerBorders(window);
    displayGameEntities(window, playership, aliens_, pod_, asteroids_, human_, playerProjectiles_, playerFuel_);
}

void displaygameEntities::displayWrapping(sf::RenderWindow& window,playerShip& playership, alien& aliens_,pod& pod_,asteroids& asteroids_,
handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_)
{
    //Inifnite scrolling 
    if(screen.isWrappingViewSet(window,playership.getPos()))
    {
    displayGameEntities(window, playership, aliens_, pod_, asteroids_, human_, playerProjectiles_, playerFuel_);
    }
}

void displaygameEntities::displayGameEntities(sf::RenderWindow &window, playerShip& playership, alien& aliens_,pod& pod_,asteroids& asteroids_
,handlingHumanoids& human_, PlayerProjectiles& playerProjectiles_,  fuel& playerFuel_)
{
    window.draw(background_sprite_);
    aliens_.display(window);
    playerFuel_.displayFuel(window);
    playership.drawto(window);
    playerProjectiles_.display(window);
    human_.display(window);
    pod_.display(window);
    asteroids_.displayAsteroids(window);
}