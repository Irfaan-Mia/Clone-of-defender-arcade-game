#ifndef SCORE_H
#define SCORE_H

/**
 * @file score.h
 * @brief This class is responsible for handling the score of the player.
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>

static std::vector<int> highScores_;
class score {
public:
    static int score_;
    /**
     * @brief Construct a new score object and initializes required textures. 
     * 
     */
    score();
    /**
     * @brief Updates the total score by integer amount passed into function. 
     * 
     * @param points_ integer value increasing or decreasing total players score. 
     */
    void updateScore(int& points_);
    /**
     * @brief Resets score to initial value of zero. 
     * 
     */
    void resetScore();
    /**
     * @brief Displays the current score of the player. 
     * 
     * @param window  Reference to RenderWindow object.
     */
    void displayScore(sf::RenderWindow& window);
    /**
     * @brief Displays the current stored top 5 highscores. 
     * 
     * @param window  Reference to RenderWindow object.
     */
    void displayHighScores(sf::RenderWindow& window);
    /**
     * @brief Updates the high scores on completion of game. 
     * 
     */
    void updateHighScore();
    /**
     * @brief Get the player score value. 
     * 
     * @return int value representing players score. 
     */
    int getScore();
    /**
     * @brief Get top 5 highscores. 
     * 
     * @return std::vector<int> containing the top 5 highscores. 
     */
    std::vector<int> getHighScores();
    /**
     * @brief Loads currently stored top 5 highscores from textfile. 
     * 
     */
    void loadHighScores();
    /**
     * @brief Saves new top 5 highscores to same textfile. 
     * 
     */
    void saveHighScores();

private:
    sf::Font font_; 
    sf::Text scoreText_;
    sf::Text highScoreText_;
    sf::Text highestScoreText_;
    sf::Color lightBlue_ = sf::Color(51,51,102);
};

#endif
