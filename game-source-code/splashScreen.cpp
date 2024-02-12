/** \file splashScreen.cpp
*/

/* Header Files */
#include "splashScreen.h"

SplashScreen::SplashScreen() {
    // Load a background image
    if (!backgroundImage_.loadFromFile("resources/splash-screen.png"))
        return;

    // Load fonts
    if (!titleFont_.loadFromFile("resources/arcade-k-font.ttf"))
        return;

    if (!font_.loadFromFile("resources/arcade-n-font.ttf"))
        return;

    // Create a text object for the title
    titleText_.setFont(titleFont_);
    titleText_.setString("Defender");
    titleText_.setCharacterSize(80);
    titleText_.setFillColor(sf::Color::Yellow);
    titleText_.setStyle(sf::Text::Bold);

    // Center the title in the window
    const sf::Vector2u windowSize_(1350, 750);
    sf::FloatRect titleRect = titleText_.getLocalBounds();
    titleText_.setOrigin(titleRect.left + titleRect.width / 2.0f,
                        titleRect.top + titleRect.height / 2.0f);
    titleText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, 110.0f);

    controlHeadingText_.setFont(titleFont_);
    controlHeadingText_.setString("Game Controls");
    controlHeadingText_.setCharacterSize(50);
    controlHeadingText_.setFillColor(sf::Color::White);
    controlHeadingText_.setStyle(sf::Text::Regular);

    sf::FloatRect controlsRect_ = controlHeadingText_.getLocalBounds();
    controlHeadingText_.setOrigin(controlsRect_.left + controlsRect_.width/2.0f, controlsRect_.top + controlsRect_.height/2.0f);
    controlHeadingText_.setPosition(sf::Vector2f(windowSize_.x/2.0f, windowSize_.y/4.0f + 50.0f)); 

    // Create a text object for the movement controls
    controlsText_.setFont(font_);
    controlsText_.setString("W\t- Move Up\nA\t- Move Left\nS\t- Move Down\nD\t- Move Right\nV\t- Shield\nSpc\t- Shoot");
    controlsText_.setCharacterSize(35);
    controlsText_.setFillColor(sf::Color::White);
    controlsText_.setStyle(sf::Text::Regular);

    // Center align the controls
    sf::FloatRect controlsBounds_ = controlsText_.getLocalBounds();
    controlsText_.setOrigin(controlsBounds_.left + controlsBounds_.width/2.0f, controlsBounds_.top + controlsBounds_.height/2.0f);
    controlsText_.setPosition(sf::Vector2f(windowSize_.x/2.0f, windowSize_.y/2.0f + 50.0f)); 

    // Create a text object for score menu
    scoreText_.setFont(font_);
    scoreText_.setString("Press 'H' to View High Scores");
    scoreText_.setCharacterSize(25);
    scoreText_.setFillColor(sf::Color::White);
    scoreText_.setStyle(sf::Text::Regular);

    // Position the continue text at the bottom of the window
    sf::FloatRect scoreRect_ = scoreText_.getLocalBounds();
    scoreText_.setOrigin(scoreRect_.left + scoreRect_.width / 2.0f,
                           scoreRect_.top + scoreRect_.height / 2.0f);
    scoreText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) - 90.0f);

    // Create a text object for instruction to continue
    continueText_.setFont(font_);
    continueText_.setString("Press Space Bar to Continue");
    continueText_.setCharacterSize(25);
    continueText_.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity_)));
    continueText_.setStyle(sf::Text::Regular);

    // Position the continue text at the bottom of the window
    sf::FloatRect continueRect = continueText_.getLocalBounds();
    continueText_.setOrigin(continueRect.left + continueRect.width / 2.0f,
                           continueRect.top + continueRect.height / 2.0f);
    continueText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) - 50.0f);
}

SplashScreen::~SplashScreen() {}

void SplashScreen::display(sf::RenderWindow& window_) {
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
    window_.draw(controlHeadingText_);
    window_.draw(controlsText_);
    window_.draw(scoreText_);
    window_.draw(continueText_);
}
