#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

/** \file splashScreen.h
    \brief Contains code for displaying the splash screen.
*/

/* Header Files */
#include <SFML/Graphics.hpp>

class SplashScreen {
public:
    /** \brief Constructor

     Creates a SplashScreen object.
    */
    SplashScreen();
    /** \brief Displays the splash screen.

     \param window Reference to sf::RenderWindow object.
     */
    ~SplashScreen();
    void display(sf::RenderWindow& window_);

private:
    sf::Clock clock_;
    float opacity_ = 255.0f;
    bool increasing_ = false;
    sf::Texture backgroundImage_;
    sf::Font titleFont_;
    sf::Font font_;
    sf::Text titleText_;
    sf::Text controlHeadingText_;
    sf::Text controlsText_;
    sf::Text scoreText_;
    sf::Text continueText_;
};

#endif // SPLASHSCREEN_H
