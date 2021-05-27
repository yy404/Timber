 #include "GameUI.hpp"

// Set resourcePath() as an empty string if not using Xcode
#ifndef RESOURCE_PATH_HPP
#define resourcePath() ""
#endif

GameUI::GameUI(float fWidth, float fHeight): m_kiFontSizeDefault(75)
{
    // Create a template text
    m_font.loadFromFile(resourcePath() + std::string("fonts/KOMIKAP_.ttf"));
    sf::Text templateText;
    templateText.setFont(m_font); // must set font to show the text
    templateText.setCharacterSize(m_kiFontSizeDefault);
    templateText.setFillColor(sf::Color::White);
    
    // Create gameplay texts
    m_pTextMessage = createTextByTemplate(templateText, sf::Vector2f(0.5f * fWidth, 0.5f * fHeight), "Press Enter To Start!");
    m_pTextTimer = createTextByTemplate(templateText, sf::Vector2f(0.5f * fWidth, fHeight - 100.0f), "Timer: 0.0");
    m_pTextScore = createTextByTemplate(templateText, sf::Vector2f(20.0f,20.0f), "Score = 0");

    // Set the orgin of some texts
    setTextOrigin(m_pTextMessage, 0.5f, 0.5f);
    setTextOrigin(m_pTextTimer, 0.5f, 0.5f);
}

GameUI::~GameUI()
{
    for (auto pText: m_vectorTextPtr)
    {
        delete pText;
    }
}

void GameUI::drawUI(sf::RenderWindow& window)
{
    for (auto pText : m_vectorTextPtr)
    {
        window.draw(*pText);
    }
}

sf::Text* GameUI::createTextByTemplate(const sf::Text& krTextTemplate, sf::Vector2f v2fPosition, std::string strTextInit)
{
    sf::Text* pText = new sf::Text(krTextTemplate);
    m_vectorTextPtr.push_back(pText);
    
    pText->setPosition(v2fPosition);
    pText->setString(strTextInit);
    
    return pText;
}

void GameUI::setTextOrigin(sf::Text* const kpText, float fRatioX, float fRatioY)
{
    sf::FloatRect textRect = kpText->getLocalBounds();

    float fOriginX = textRect.left + (fRatioX * textRect.width);
    float fOriginY = textRect.top + (fRatioY * textRect.height);

    kpText->setOrigin(fOriginX, fOriginY);
}

void GameUI::updateMessage(std::string strMsg)
{
    m_pTextMessage->setString(strMsg);
    setTextOrigin(m_pTextMessage, 0.5f, 0.5f);
}

void GameUI::updateTimer(float fTime)
{
    std::string strTemp = "Timer: ";
    strTemp += std::to_string(fTime).substr(0,3); // keep 3 chars
    m_pTextTimer->setString(strTemp);
}

void GameUI::updateScore(int iScore)
{
    std::string strTemp = "Score = ";
    strTemp += std::to_string(iScore);
    m_pTextScore->setString(strTemp);
}
