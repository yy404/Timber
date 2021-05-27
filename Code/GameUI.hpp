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
    GameUI(float fWidth, float fHeight);
    ~GameUI();

    GameUI(const GameUI&) = delete;
    GameUI(GameUI&&) = delete;

    void drawUI(sf::RenderWindow& window);
    
    void updateMessage(std::string strMsg);
    void updateTimer(float fTime);
    void updateScore(int iScore);
    
private:
    sf::Text* createTextByTemplate(const sf::Text& krTextTemplate, sf::Vector2f v2fPosition, std::string strTextInit);
    void setTextOrigin(sf::Text* const kpText, float fRatioX, float fRatioY);

    sf::Font m_font;
    const int m_kiFontSizeDefault;

    std::vector<sf::Text*> m_vectorTextPtr;
    sf::Text* m_pTextMessage;
    sf::Text* m_pTextTimer;
    sf::Text* m_pTextScore;
};
