/** \file main.cpp
    \brief Contains the main function of the game
*/

/* Header Files */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "screenManager.h"

/* Global Constants */
const float pi = 3.14159f; /**< Pi */
const int gameWidth = 1350; /**< The width of the game screen */
const int gameHeight = 750; /**< The height of the game screen */

/** \fn int main()
 *  \brief This function contains the majority of the code for the game
 *
 *  \return The application exit code: 0 for successful completion; a negative number to indicate an error
 *
 */
int main()
{
    // Create the window of the application
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "SFML Defender", sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true); // Automatic frame rate
    
    // Create application icon
	sf::Image icon;
    if (!icon.loadFromFile("resources/app-icon.png"))
        return EXIT_FAILURE;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    //Background Music
    sf::Music backgroundMusic; 
    if(!backgroundMusic.openFromFile("resources/background-music.wav"))
    {
        std::cerr << "Failed to load background music" << std::endl;
        return EXIT_FAILURE;
    }

    backgroundMusic.setVolume(10);
    backgroundMusic.setLoop(true);
    backgroundMusic.play(); 

    // Create a screen manager object
    ScreenManager screenManager;
    score playerScore;
    playerScore.loadHighScores();
    
    // Run the program as long as the window is open
    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close the application window if 'ESC' is presssed or window is closed
            if((event.type == sf::Event::Closed) ||
	        ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) {
                playerScore.saveHighScores();
		        window.close();
		    break;
	        }
            // std::cout << playerScore_.getScore() << std::endl;
            screenManager.update(window, event);
        }
        //Temporary as it fixed hit registration when players ship is still in its spawn location//
        screenManager.update(window, event);
        window.clear();
        screenManager.display(window);
        window.display();
    }

    return EXIT_SUCCESS;
}