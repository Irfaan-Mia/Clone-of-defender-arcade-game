/** \file scoreScreen.cpp
*/

/* Header Files */
#include "scoreScreen.h"

ScoreScreen::ScoreScreen() {
    // Load a background image
    if (!backgroundImage_.loadFromFile("resources/splash-screen.png"))
        return;

    // Load fonts
    if (!titleFont_.loadFromFile("resources/arcade-k-font.ttf"))
        return;

    if (!font_.loadFromFile("resources/arcade-n-font.ttf"))
        return;

    const sf::Vector2u windowSize_(1350, 750);

    // Create a text object for the title
    titleText_.setFont(titleFont_);
    titleText_.setString("High Scores");
    titleText_.setCharacterSize(80);
    titleText_.setFillColor(sf::Color::Yellow);
    titleText_.setStyle(sf::Text::Bold);

    // Center the title in the window
    sf::FloatRect titleRect = titleText_.getLocalBounds();
    titleText_.setOrigin(titleRect.left + titleRect.width / 2.0f,
                        titleRect.top + titleRect.height / 2.0f);
    titleText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, 110.0f);

    subHeadingText_.setFont(titleFont_);
    subHeadingText_.setString("Top 5 Scores");
    subHeadingText_.setCharacterSize(50);
    subHeadingText_.setFillColor(sf::Color::White);
    subHeadingText_.setStyle(sf::Text::Regular);

    // Center align the title
    sf::FloatRect subRect_ = subHeadingText_.getLocalBounds();
    subHeadingText_.setOrigin(subRect_.left + subRect_.width/2.0f, subRect_.top + subRect_.height/2.0f);
    subHeadingText_.setPosition(sf::Vector2f(windowSize_.x/2.0f, windowSize_.y/4.0f + 50.0f)); 

    // Create a text object for instruction to continue
    continueText_.setFont(font_);
    continueText_.setString("Press Space Bar To Return To The Menu");
    continueText_.setCharacterSize(25);
    continueText_.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity_)));
    continueText_.setFillColor(sf::Color::White);
    continueText_.setStyle(sf::Text::Regular);

    // Position the continue text at the bottom of the window
    sf::FloatRect continueRect = continueText_.getLocalBounds();
    continueText_.setOrigin(continueRect.left + continueRect.width / 2.0f,
                           continueRect.top + continueRect.height / 2.0f);
    continueText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) - 50.0f);
}

ScoreScreen::~ScoreScreen() {}

void ScoreScreen::display(sf::RenderWindow& window_) {
    // Vary text opacity
    sf::Time elapsed_ = clock_.restart();
    float change_ = elapsed_.asSeconds() * 100.0f;

    if (increasing_)
    {
        opacity_ += change_;
        if (opacity_ >= 255.0f)
        {
            opacity_ = 255.0f;
            increasing_ = false;
        }
    }
    else
    {
        opacity_ -= change_;
        if (opacity_ <= 127.5f) // 50% of 255
        {
            opacity_ = 127.5f;
            increasing_ = true;
        }
    }
    continueText_.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity_)));
    
    // Draw the background image
    sf::Sprite background(backgroundImage_);
    window_.draw(background);

    // Draw the title and controls text
    window_.draw(titleText_);
    window_.draw(subHeadingText_);
    window_.draw(continueText_);
    playerScore_.displayHighScores(window_);
}
