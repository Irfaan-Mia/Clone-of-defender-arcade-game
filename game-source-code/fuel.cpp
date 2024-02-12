/** \file fuel.cpp
*/

/* Header Files */
#include "fuel.h"

int fuel::totalFuel_ = 100; 

fuel::fuel()
{
    if(!fuel_texture.loadFromFile("resources/fuel.png"))
    {
        std::cerr << "ERROR::LOADING fuel.png" << std::endl;
        return;
    }
    if(!font.loadFromFile("resources/arcade-n-font.ttf"))
    {
        std::cerr << "ERROR::LOADING defender-font.ttf" << std::endl;
        return;
    }
    
    const sf::Vector2u windowSize(1350, 750);
    float topLeftX = 10.0f; 
    float topLeftY = static_cast<float>(windowSize.y) * 0.05f; 

    //Fuel
    sf::Color backFuelBar = sf::Color(0,0,51);
    playerfuelBar_.setSize({ 300.0f, 25.0f });
    playerfuelBar_.setPosition({ topLeftX + 10, topLeftY + 40.0f });
    playerfuelBarInverted_.setSize({ 300.0f, 25.0f });
    playerfuelBarInverted_.setPosition({ topLeftX + 10, topLeftY + 40.0f });
    playerfuelbarBack_.setSize({ 320.0f, 35.0f });
    playerfuelbarBack_.setPosition({ topLeftX, topLeftY + 35.0f });
    playerfuelBar_.setFillColor(sf::Color::Red);
    playerfuelBarInverted_.setFillColor(backFuelBar);
    playerfuelbarBack_.setFillColor(sf::Color::White);

    //Text for fuel percentage 
    textfuelPercentage.setFont(font); 
    textfuelPercentage.setFillColor(sf::Color::Yellow);
    textfuelPercentage.setPosition({ topLeftX, topLeftY });
    textfuelPercentage.setCharacterSize(20);
}

fuel::~fuel()
{
}

void fuel::spawnFuel()
{
    static clock_t spawnTimer_ = clock();
    auto currentTime_ = clock();
    auto elapsedTime_ = static_cast<double>(currentTime_ - spawnTimer_) / CLOCKS_PER_SEC * 1000;
    auto spawnInterval_ = fuelspawnInterval;
    auto despawnInterval_ = fueldespawnInterval;


    if (elapsedTime_ >= spawnInterval_ && fuelCount_ < maxFuel_) {
    sf::Sprite fuel; 
    fuel.setTexture(fuel_texture);
    fuel.setScale({0.035f,0.035f});

    //Need to randomize fuel spawn position
    auto randX_ = static_cast<float>(std::rand() % (static_cast<int>(maxscreenSize.x) - 100)); 
    auto randY_ = maxscreenSize.y*0.99f - fuel.getGlobalBounds().height;

    //Check if spawning ontop of one another
    while(checkfuelOverlap(fuel,randX_,randY_))
    {
        auto randX_ = static_cast<float>(std::rand() % (static_cast<int>(maxscreenSize.x) - 100)); 
    }
    fuel.setPosition({randX_,randY_});
    addfuel(fuel);
    fuelCount_++;
    spawnTimer_ = currentTime_;
    }
    if(elapsedTime_ >= despawnInterval_ && Fuel_.size() == maxFuel_)
    {
        Fuel_.clear();
        fuelCount_ = 0;
        spawnTimer_ = currentTime_;
    }

}

bool fuel::checkfuelOverlap(sf::Sprite test,float randX_, float randY_)
{
    if(!Fuel_.empty())
    {
        for(auto& fuel: Fuel_)
        {
        sf::FloatRect fuelBounds_ = fuel.getGlobalBounds();
        sf::FloatRect fuelcanisterBounds_ = test.getGlobalBounds();
        if(fuelBounds_.intersects(fuelcanisterBounds_))
        {
            return true; 
        }
        }
    }
    return false;
}



void fuel::checkcollisionwithFuel(sf::FloatRect playerPos)
{
    for(auto i = 0; i < Fuel_.size(); i++) 
    {
        sf::FloatRect playerBounds_ = playerPos;
        sf::FloatRect fuelBounds_ = Fuel_[i].getGlobalBounds(); 

        if(playerBounds_.intersects(fuelBounds_))
        {
            Fuel_.erase(Fuel_.begin() + i);
            fuelCount_--; 
            totalFuel_+=20; 
            if(totalFuel_ > 100)
            {
                totalFuel_ = 100;
            }
        }
    }
}

bool fuel::doesplayerhaveFuel()
{
    return totalFuel_ != 0;
}

void fuel::decreasefuel()
{
    static clock_t spawnTimer_ = clock();
    auto currentTime_ = clock();
    auto elapsedTime_ = static_cast<double>(currentTime_ - spawnTimer_) / CLOCKS_PER_SEC * 1000;
    auto spawnInterval_ = fuelconsumptionInterval;


    if (elapsedTime_ >= spawnInterval_ && totalFuel_ > 0) {
    decrementfuel(); 
    spawnTimer_ = currentTime_;
    }
}

void fuel::addfuel(sf::Sprite fuel)
{
    Fuel_.push_back(fuel);
}

void fuel::decrementfuel()
{
     totalFuel_-=fuelConsumption;
}

void fuel::displayFuel(sf::RenderWindow &window)
{
    for(auto& fuel: Fuel_)
    {
        window.draw(fuel);
    }
}

void fuel::updatefuelGauge()
{
 float fuelPercentage = static_cast<float>(totalFuel_)/100;
 playerfuelBar_.setSize({300.0f*fuelPercentage,25.0f}); 
}

void fuel::displayfuelGauge(sf::RenderWindow& window)
{
    updatefuelGauge();
    std::string fuelPercentage = std::to_string(static_cast<int>(round(static_cast<float>(totalFuel_)/100 * 100)));
    textfuelPercentage.setString("Fuel: " + fuelPercentage); 
    window.draw(textfuelPercentage);
    window.draw(playerfuelbarBack_);
    window.draw(playerfuelBarInverted_);
    window.draw(playerfuelBar_);
}

sf::Vector2f fuel::getcrashingSpeed()
{
 return crashingSpeed_;
}

void fuel::resetFuel()
{
    totalFuel_ = 100; 
    Fuel_.clear();
    fuelCount_ = 0;
}

std::vector<sf::Sprite> fuel::getfuel()
{
    return Fuel_;
}

int fuel::gettotalFuel()
{
    return totalFuel_;
}

