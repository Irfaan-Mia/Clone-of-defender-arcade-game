#ifndef PREGAMESCREEN_H
#define PREGAMESCREEN_H

/** \file preGameScreen.h
    \brief Contains code for displaying the pre game screen.
*/

/* Header Files */
#include <SFML/Graphics.hpp>
#include <vector>

class PreGameScreen {
public:
    /** \brief Constructor

     Creates a PreGameScreen object.
    */
    PreGameScreen();
    /**
     * @brief Destroy the Pre Game Screen object
     * 
     */
    ~PreGameScreen();
    /** \brief Displays the pre game screen.

     \param window Reference to sf::RenderWindow object.
     */
    void display(sf::RenderWindow& window_);

private:
    sf::Clock clock_;
    float opacity_ = 255.0f;
    bool increasing_ = false;
    sf::Color darkBlue_ = sf::Color(0,0,51);
    sf::Font titleFont_;
    sf::Font font_;
    sf::Text titleText_;
    sf::Text continueText_;
    struct variousEnemies_ {
        sf::Texture texture_;
        sf::Sprite sprite_;
        sf::Text name_;
        sf::Text points_;
    };

    std::vector<std::string> enemyNames_ = {"lander", "pod", "swarmer"};
    std::vector<int> enemyPoints_ = {150, 1000, 150}; 
    std::vector<variousEnemies_> enemies_;
    std::vector<sf::Texture> textures_;
};

#endif // PREGAMESCREEN_H
