/** \file gameoverScreen.cpp
*/

/* Header Files */

#include "gameoverScreen.h"
#include <iostream>

GameOverScreen::GameOverScreen()
{
    if(!background_image.loadFromFile("resources/splash-screen.png"))
    {
        std::cerr <<"splash-screen.png cannot be found" << std::endl;
        return; 
    }
    if(!font.loadFromFile("resources/arcade-n-font.ttf"))
    {
        std::cerr <<"arcade-n-font.ttf cannot be found" << std::endl;
        return;
    }

    const sf::Vector2u windowSize_(1350, 750);

    //Game Over Text
    GameOverText.setFont(font); 
    GameOverText.setStyle(sf::Text::Bold);
    GameOverText.setString("GAME OVER");
    GameOverText.setCharacterSize(40); 
    GameOverText.setFillColor(sf::Color::Black);
    GameOverText.setOutlineColor(sf::Color::White); 
    GameOverText.setOutlineThickness(5.0f);
    
    // Calculate the position to center the text
    sf::FloatRect textBounds = GameOverText.getLocalBounds();
    GameOverText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                         textBounds.top + textBounds.height / 2.0f);
    
    //Game Over Text : Win
    winnerText_.setFont(font); 
    winnerText_.setStyle(sf::Text::Bold);
    winnerText_.setString("YOU WIN");
    winnerText_.setCharacterSize(40); 
    winnerText_.setFillColor(sf::Color::Green);
    winnerText_.setOutlineColor(sf::Color::White); 
    winnerText_.setOutlineThickness(5.0f);
    
    // Calculate the position to center the text
    sf::FloatRect winnerTextBounds_ = winnerText_.getLocalBounds();
    winnerText_.setOrigin(winnerTextBounds_.left + winnerTextBounds_.width / 2.0f,
                         winnerTextBounds_.top + winnerTextBounds_.height / 2.0f);

    // Game Over Text: Lose
    loserText_.setFont(font);
    loserText_.setStyle(sf::Text::Bold);
    loserText_.setString("YOU LOSE"); // Change the text as needed
    loserText_.setCharacterSize(40);
    loserText_.setFillColor(sf::Color::White);
    loserText_.setOutlineColor(sf::Color::Red);
    loserText_.setOutlineThickness(5.0f);

    // Calculate the position to center the text
    sf::FloatRect loserTextBounds_ = loserText_.getLocalBounds();
    loserText_.setOrigin(loserTextBounds_.left + loserTextBounds_.width / 2.0f,
                         loserTextBounds_.top + loserTextBounds_.height / 2.0f);

    scoreText_.setFont(font); 
    scoreText_.setStyle(sf::Text::Bold);
    scoreText_.setString("Score: " + std::to_string(playerScore_));
    scoreText_.setCharacterSize(40); 
    scoreText_.setFillColor(sf::Color::White);
    scoreText_.setOutlineColor(sf::Color::Blue); 
    scoreText_.setOutlineThickness(5.0f);

    sf::FloatRect scoreTextBounds_ = scoreText_.getLocalBounds();
    scoreText_.setOrigin(scoreTextBounds_.left + scoreTextBounds_.width / 2.0f,
                         scoreTextBounds_.top + scoreTextBounds_.height / 2.0f);

    // Calculate the total height of all texts
    float totalHeight = textBounds.height + winnerTextBounds_.height + loserTextBounds_.height + scoreTextBounds_.height;

    // Adjust the positions of the texts
    GameOverText.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) / 2.0f - totalHeight / 2.0f + textBounds.height / 2.0f);
    winnerText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) / 2.0f - totalHeight / 2.0f + textBounds.height + winnerTextBounds_.height / 2.0f);
    loserText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) / 2.0f - totalHeight / 2.0f + textBounds.height + loserTextBounds_.height / 2.0f);
    scoreText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) / 2.0f - totalHeight / 2.0f + textBounds.height + winnerTextBounds_.height + scoreTextBounds_.height / 2.0f);


    //Restart game text
    RestartText.setFont(font);  
    RestartText.setStyle(sf::Text::Regular);
    RestartText.setString("Press Space Bar to restart or ESC to exit");
    RestartText.setFillColor(sf::Color::White);
    RestartText.setCharacterSize(25); 

    // Position the restart text at the bottom of the window
    sf::FloatRect restartRect_ = RestartText.getLocalBounds();
    RestartText.setOrigin(restartRect_.left + restartRect_.width / 2.0f,
                           restartRect_.top + restartRect_.height / 2.0f);
    RestartText.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) - 50.0f);
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::display(sf::RenderWindow &window, bool &isWinner_, int score_)
{
    sf::Sprite background(background_image);
    window.draw(background);
    window.draw(GameOverText);
    if (isWinner_)
    {
        window.draw(winnerText_);
    } else
    {
        window.draw(loserText_);
    }
    playerScore_ = score_;
    sf::FloatRect scoreTextBounds_ = scoreText_.getLocalBounds();
    scoreText_.setOrigin(scoreTextBounds_.left + scoreTextBounds_.width / 2.0f,
                         scoreTextBounds_.top + scoreTextBounds_.height / 2.0f);
    scoreText_.setString(std::to_string(playerScore_) + " PTS");
    window.draw(scoreText_);
    window.draw(RestartText);
}
