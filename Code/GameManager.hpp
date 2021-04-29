#pragma once
#include <SFML/Graphics.hpp>

class GameManager
{
public:
    GameManager();
    void newGame();
    bool checkEnd();
    void decTimer(float);
    float calDeltaTime();
    
private:
    bool paused;
    bool acceptInput;
    int score;
    
    const float timerValMax;
    float timerVal;
    sf::Clock clock;
    
    friend class GameEngine;
};
