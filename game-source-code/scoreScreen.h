#ifndef SCORESCREEN_H
#define SCORESCREEN_H

/**
 * @file scoreScreen.h
 * @brief This class is responsible for displaying the top 5 highscores. 
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* Header Files */
#include <SFML/Graphics.hpp>
#include "score.h"

class ScoreScreen {
public:
    /**
     * @brief Construct a new Score Screen object. The initialization of required textures and fonts are performed. 
     * 
     */
    ScoreScreen();
    /**
     * @brief Destroy the Score Screen object
     * 
     */
    ~ScoreScreen();
    /**
     * @brief Displays required text, background and values of top 5 highscores. 
     * 
     * @param window_ Reference to RenderWindow object.
     */
    void display(sf::RenderWindow& window_);

private:
    score playerScore_;
    sf::Clock clock_;
    float opacity_ = 255.0f;
    bool increasing_ = false;
    sf::Texture backgroundImage_;
    sf::Font titleFont_;
    sf::Font font_;
    sf::Text titleText_;
    sf::Text subHeadingText_;
    sf::Text continueText_;
};

#endif // SCORESCREEN_H
