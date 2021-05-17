 #include "GameUI.hpp"

// Set resourcePath() as an empty string if not using Xcode
#ifndef RESOURCE_PATH_HPP
#define resourcePath() ""
#endif

GameUI::GameUI(float width, float height): fontSizeDefault(75)
{
    // Create a template text
    font.loadFromFile(resourcePath() + std::string("fonts/KOMIKAP_.ttf"));
    sf::Text templateText;
    templateText.setFont(font); // must set font to show the text
    templateText.setCharacterSize(fontSizeDefault);
    templateText.setFillColor(sf::Color::White);
    
    // Create gameplay texts
    messageTextPtr = createTextByTemplate(templateText, sf::Vector2f(0.5f * width, 0.5f * height), "Press Enter To Start!");
    timerTextPtr = createTextByTemplate(templateText, sf::Vector2f(0.5f * width, height - 100.0f), "Timer: 0.0");
    scoreTextPtr = createTextByTemplate(templateText, sf::Vector2f(20.0f,20.0f), "Score = 0");

    // Set the orgin of some texts
    setTextOrigin(messageTextPtr, 0.5f, 0.5f);
    setTextOrigin(timerTextPtr, 0.5f, 0.5f);
}

GameUI::~GameUI()
{
    for (auto textPtr: textPtrVector)
    {
        delete textPtr;
    }
}

void GameUI::drawUI(sf::RenderWindow& window)
{
    for (auto textPtr: textPtrVector)
    {
        window.draw(*textPtr);
    }
}

sf::Text* GameUI::createTextByTemplate(const sf::Text& templateText, sf::Vector2f position, std::string initText)
{
    sf::Text* newTextPtr = new sf::Text(templateText);
    textPtrVector.push_back(newTextPtr);
    
    newTextPtr->setPosition(position);
    newTextPtr->setString(initText);
    
    return newTextPtr;
}

void GameUI::setTextOrigin(sf::Text* const textPtr, float xRatio, float yRatio)
{
    sf::FloatRect textRect = textPtr->getLocalBounds();

    float xOrigin = textRect.left + (xRatio * textRect.width);
    float yOrigin = textRect.top + (yRatio * textRect.height);

    textPtr->setOrigin(xOrigin, yOrigin);
}

void GameUI::updateMessage(std::string msg)
{
    messageTextPtr->setString(msg);
    setTextOrigin(messageTextPtr, 0.5f, 0.5f);
}

void GameUI::updateTimer(float time)
{
    std::string temp = "Timer: ";
    temp += std::to_string(time).substr(0,3); // keep 3 chars
    timerTextPtr->setString(temp);
}

void GameUI::updateScore(int val)
{
    std::string temp = "Score = ";
    temp += std::to_string(val);
    scoreTextPtr->setString(temp);
}
