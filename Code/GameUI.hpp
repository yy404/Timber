#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector> // Using a vector to record all texts

// In case of using Xcode
#ifdef XCODE_VERSION
#include "ResourcePath.hpp"
#endif

class GameUI
{
public:
    GameUI(float, float);
    ~GameUI();

    GameUI(const GameUI&) = delete;
    GameUI(GameUI&&) = delete;

    void drawUI(sf::RenderWindow&);
    
    void updateMessage(std::string);
    void updateTimer(float);
    void updateScore(int);
    
private:
    sf::Text* createTextByTemplate(const sf::Text&, sf::Vector2f, std::string);
    void setTextOrigin(sf::Text* const, float, float);

    sf::Font font;
    const int fontSizeDefault;

    std::vector<sf::Text*> textPtrVector;
    sf::Text* messageTextPtr;
    sf::Text* timerTextPtr;
    sf::Text* scoreTextPtr;
};
