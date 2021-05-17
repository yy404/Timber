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
    GameUI(float width, float height);
    ~GameUI();

    GameUI(const GameUI&) = delete;
    GameUI(GameUI&&) = delete;

    void drawUI(sf::RenderWindow& window);
    
    void updateMessage(std::string msg);
    void updateTimer(float time);
    void updateScore(int val);
    
private:
    sf::Text* createTextByTemplate(const sf::Text& templateText, sf::Vector2f position, std::string initText);
    void setTextOrigin(sf::Text* const textPtr, float xRatio, float yRatio);

    sf::Font font;
    const int fontSizeDefault;

    std::vector<sf::Text*> textPtrVector;
    sf::Text* messageTextPtr;
    sf::Text* timerTextPtr;
    sf::Text* scoreTextPtr;
};
