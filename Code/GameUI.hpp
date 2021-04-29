#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ResourcePath.hpp"

class GameUI
{
public:
    GameUI();
    ~GameUI();
    void drawUI(sf::RenderWindow&);
    
    void updateMessage(std::string);
    void updateTimer(float);
    void updateScore(int);
    
private:
    sf::Text* createTextByTemplate(sf::Text&, sf::Vector2f, std::string);
    std::vector<sf::Text*> textPtrVector;

    sf::Font font;
    const int fontSizeDefault;
    
    sf::Text* messageTextPtr;
    sf::Text* timerTextPtr;
    sf::Text* scoreTextPtr;
};
