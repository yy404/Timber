 #include "GameUI.hpp"

GameUI::GameUI(): fontSizeDefault(75)
{
    // create template text
    font.loadFromFile(resourcePath() + "fonts/KOMIKAP_.ttf");
    sf::Text templateText;
    templateText.setFont(font); // must set font to show the text
    templateText.setCharacterSize(fontSizeDefault);
    templateText.setFillColor(sf::Color::White);
    
    // create gameplay text
    messageTextPtr = createTextByTemplate(templateText, sf::Vector2f(0,0), "Press Enter To Start");
    timerTextPtr = createTextByTemplate(templateText, sf::Vector2f(0,100), "Timer:");
    scoreTextPtr = createTextByTemplate(templateText, sf::Vector2f(0,200), "Score:");
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

sf::Text* GameUI::createTextByTemplate(sf::Text& templateText, sf::Vector2f position, std::string initText)
{
    sf::Text* newTextPtr = new sf::Text(templateText);
    textPtrVector.push_back(newTextPtr);
    
    newTextPtr->setPosition(position);
    newTextPtr->setString(initText);
    
    return newTextPtr;
}

void GameUI::updateMessage(std::string msg)
{
    messageTextPtr->setString(msg);
}

void GameUI::updateTimer(float time)
{
    std::string temp = "Timer: ";
    temp += std::to_string(time).substr(0,3); // keep 3 chars
    timerTextPtr->setString(temp);
}

void GameUI::updateScore(int val)
{
    std::string temp = "Score: ";
    temp += std::to_string(val);
    scoreTextPtr->setString(temp);
}
