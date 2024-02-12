/** \file score.cpp
*/

/* Header Files */
#include "score.h"

score::score() {
    if (!font_.loadFromFile("resources/arcade-n-font.ttf"))
        return;
    
    const sf::Vector2u windowSize_(1350, 750);

    scoreText_.setFont(font_);
    scoreText_.setCharacterSize(20);
    scoreText_.setFillColor(sf::Color::Yellow);
    float topRightX_ = static_cast<float>(windowSize_.x) - 250.0f;
    float topRightY = static_cast<float>(windowSize_.y) * 0.05f;
    scoreText_.setPosition(topRightX_, topRightY);
    scoreText_.setString("Score: " + std::to_string(0));

    highestScoreText_.setFont(font_);
    highestScoreText_.setCharacterSize(20);
    highestScoreText_.setFillColor(lightBlue_);
    topRightX_ = static_cast<float>(windowSize_.x) - 250.0f;
    topRightY = static_cast<float>(windowSize_.y) * 0.08f;
    highestScoreText_.setPosition(topRightX_, topRightY);

    highScoreText_.setFont(font_);
    highScoreText_.setCharacterSize(35);
    highScoreText_.setFillColor(sf::Color::White);
}

void score::updateScore(int& points_) {
    score_ += points_;
}

void score::resetScore() {
    score_ = 0;
}

void score::updateHighScore() 
{
    highScores_.push_back(score_);

    std::sort(highScores_.begin(), highScores_.end(), std::greater<int>());
    
    if (highScores_.size() > 5) 
    {
        highScores_.resize(5); // Keep only the top 5 high scores
    }
}

int score::getScore() {
    return score_;
}

std::vector<int> score::getHighScores()
{
    return highScores_;
}

void score::displayScore(sf::RenderWindow& window) {
    scoreText_.setString("Score: " + std::to_string(score_));

    if (!highScores_.empty()) {
        highestScoreText_.setString("High\nScore: " + std::to_string(highScores_[0]));
    }

    window.draw(scoreText_);
    window.draw(highestScoreText_);
}

void score::displayHighScores(sf::RenderWindow& window_) 
{   
    const sf::Vector2u windowSize_(1350, 750);

    std::stringstream ss_;

    for (int i = 0; i < highScores_.size(); ++i) 
    {
        ss_ << std::left << std::setw(5) << i + 1 << std::setw(2) << highScores_[i] << "\n";
    }

    highScoreText_.setString(ss_.str());
    sf::FloatRect scoresBounds_ = highScoreText_.getLocalBounds();
    highScoreText_.setOrigin(scoresBounds_.left + scoresBounds_.width/2.0f, scoresBounds_.top + scoresBounds_.height/2.0f);
    highScoreText_.setPosition(sf::Vector2f(windowSize_.x/2.0f, windowSize_.y/2.0f + 50.0f));
    window_.draw(highScoreText_);
}

int score::score_ = 0;

void score::loadHighScores() 
{
    std::ifstream file_("high-scores.txt");
    int currentScore_;

    while (file_ >> currentScore_) 
    {
        highScores_.push_back(currentScore_);
    }
}

void score::saveHighScores() 
{
    std::ofstream file_("high-scores.txt");
    std::cout << "high-scores" << highScores_.size() << std::endl;

    for (auto currentScore_ : highScores_) 
    {
        file_ << currentScore_ << "\n";
    }

    file_.close();
}
