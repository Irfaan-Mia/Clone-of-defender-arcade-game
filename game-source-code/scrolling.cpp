#include "scrolling.h"
#include "iostream"

scrolling::scrolling()
{
    auto lineWidth_ = 5;
    LeftBorder_.setSize(sf::Vector2f(lineWidth_, 750.0f));  
    LeftBorder_.setFillColor(sf::Color::Green);

    RightBorder_.setSize(sf::Vector2f(lineWidth_, 750.0f)); 
    RightBorder_.setFillColor(sf::Color::Magenta);
}

void scrolling::setScrolling(sf::RenderWindow &window)
{
    gameView_.setSize(window.getSize().x, window.getSize().y); 
    gameView_.setViewport(sf::FloatRect(0,0.175f,1.0f,1.0f));

    infoView_.setSize(window.getSize().x, window.getSize().y*0.175f); 
    infoView_.setCenter(window.getSize().x/2.0f,window.getSize().y*0.175f/2.0f);
    infoView_.setViewport(sf::FloatRect(0,0,1.0f,0.175f));

    miniMap_.setSize(maxgameView_,window.getSize().y*1.2f); 
    miniMap_.setCenter(maxgameView_/2.0f,750.0f*0.83f/2.0f);
    miniMap_.setViewport(sf::FloatRect(0.3f,0.0f,0.4f,0.175f));

    rightView_.setSize(window.getSize().x, window.getSize().y);
    rightView_.setCenter(maxgameView_/2.0f,rightView_.getCenter().y);
    rightView_.setViewport(sf::FloatRect(0.0f,0.175f,1.0f,1.0f));

    leftView_.setSize(window.getSize().x, window.getSize().y); 
    leftView_.setCenter(maxgameView_/2.0f,leftView_.getCenter().y);
    leftView_.setViewport(sf::FloatRect(0.0f,0.175f,1.0f,1.0f));
}

void scrolling::setviewgameView(sf::RenderWindow& window, sf::Vector2f playerPos)
{
    gameView_.setCenter(playerPos.x, gameView_.getCenter().y);
    window.setView(gameView_);
}

void scrolling::setviewinfoView(sf::RenderWindow &window)
{
    window.setView(infoView_);
}

void scrolling::setviewminimapView(sf::RenderWindow &window)
{
    window.setView(miniMap_);
}

void scrolling::setPlayerBorders(sf::Vector2f playerPos)
{
    if(playerPos.x > 1350.0f/2.0f && playerPos.x < maxgameView_ - 1350.0f/2.0f)
    {
        LeftBorder_.setPosition(playerPos.x - 1350.0f/2.0f, 0.0f); 
        RightBorder_.setPosition(playerPos.x + 1350.0f/2.0f, 0.0f); 
    }
    else if(playerPos.x < 1350.0f/2.0f)
    {
        LeftBorder_.setPosition(3000.0f - 1350.0f/2.0f + playerPos.x,0.0f);
        RightBorder_.setPosition(playerPos.x +1350.0f/2.0f,0.0f);
    }
    else if(playerPos.x > maxgameView_ - 1350.0f/2.0f)
    {
        RightBorder_.setPosition(playerPos.x-3000.0f + 1350.0f/2.0f,0.0f);
        LeftBorder_.setPosition(playerPos.x - 1350.0f/2.0f, 0.0f);
    }
    //scrolling::playerPos = playerPos;
}

void scrolling::drawPlayerBorders(sf::RenderWindow &window)
{
    window.draw(LeftBorder_); 
    window.draw(RightBorder_);
}

sf::View &scrolling::getgameView()
{
    return gameView_;
}

const sf::RectangleShape &scrolling::LeftBorder()
{
    return LeftBorder_;
}

const sf::RectangleShape &scrolling::RightBorder()
{
    return RightBorder_;
}

bool scrolling::isWrappingViewSet(sf::RenderWindow &window, sf::Vector2f playerPos)
{
    if(playerPos.x >= maxgameView_-window.getSize().x/2.0f)
    {
    rightView_.setCenter(playerPos.x - maxgameView_,rightView_.getCenter().y);
    window.setView(rightView_);
    return true; 
    }
    else if(playerPos.x <= window.getSize().x/2.0f)
    {
    leftView_.setCenter(maxgameView_ + playerPos.x, leftView_.getCenter().y);
    window.setView(leftView_);
    return true;
    }
    return false; 
}
