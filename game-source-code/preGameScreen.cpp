/** \file splashScreen.cpp
*/

/* Header Files */
#include "preGameScreen.h"

PreGameScreen::PreGameScreen() 
{
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

    // Create a text object for instruction to continue
    continueText_.setFont(font_);
    continueText_.setString("Press Space Bar to Continue");
    continueText_.setCharacterSize(25);
    continueText_.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity_)));
    continueText_.setFillColor(sf::Color::White);
    continueText_.setStyle(sf::Text::Regular);

    // Position the continue text at the bottom of the window
    sf::FloatRect continueRect_ = continueText_.getLocalBounds();
    continueText_.setOrigin(continueRect_.left + continueRect_.width / 2.0f,
                           continueRect_.top + continueRect_.height / 2.0f);
    continueText_.setPosition(static_cast<float>(windowSize_.x) / 2.0f, static_cast<float>(windowSize_.y) - 50.0f);

    textures_.resize(enemyNames_.size()); // Resize the vector
    for (int i = 0; i < enemyNames_.size(); ++i) 
    {
        if (!textures_[i].loadFromFile("resources/enemy-" + enemyNames_[i] + ".png"))
            return;
    }

    float spaceBetweenSprites_ = 200.0f; // Space between sprites
    float totalWidth = (enemyNames_.size() - 1) * spaceBetweenSprites_; // Total width of all spaces

    for (int i = 0; i < enemyNames_.size(); ++i) 
    {
        variousEnemies_ enemy_;
        enemy_.sprite_.setTexture(textures_[i]); // Use of preloaded texture

        // Center position the sprite
        float spriteX_ = windowSize_.x / 2.1f - totalWidth / 2.1f + i * spaceBetweenSprites_;
        float spriteY_ = windowSize_.y / 2.0f;
        enemy_.sprite_.setPosition(spriteX_, spriteY_);

        enemy_.name_.setFont(font_);
        enemy_.name_.setString(enemyNames_[i]);
        enemy_.name_.setCharacterSize(35);
        enemy_.name_.setFillColor(sf::Color::Yellow);

        // Center position the name under the sprite
        sf::FloatRect nameBounds_ = enemy_.name_.getLocalBounds();
        float nameX_ = spriteX_ + enemy_.sprite_.getGlobalBounds().width / 2.0f - nameBounds_.width / 2.0f;
        float nameY_ = spriteY_ + 50.0f;
        enemy_.name_.setPosition(nameX_, nameY_);

        enemy_.points_.setFont(font_);
        enemy_.points_.setString(std::to_string(enemyPoints_[i]));
        enemy_.points_.setCharacterSize(35);
        enemy_.points_.setFillColor(sf::Color::Yellow);

        // Center position the points under the name
        sf::FloatRect pointsBounds_ = enemy_.points_.getLocalBounds();
        float pointsX_ = nameX_ + nameBounds_.width / 2.0f - pointsBounds_.width / 2.0f;
        float pointsY_ = nameY_ + nameBounds_.height + 20.0f;
        enemy_.points_.setPosition(pointsX_, pointsY_);

        enemies_.push_back(enemy_);
    }
}

PreGameScreen::~PreGameScreen() {}

void PreGameScreen::display(sf::RenderWindow& window_) 
{
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
    
    // Draw the title and continue text
    window_.clear(darkBlue_);
    window_.draw(titleText_);
    window_.draw(continueText_);

    // Draw the enemies
    for (const auto& enemy_ : enemies_) {
        window_.draw(enemy_.sprite_);
        window_.draw(enemy_.name_);
        window_.draw(enemy_.points_);
    }
}
