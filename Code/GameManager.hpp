#pragma once
#include <SFML/Graphics.hpp>

class GameManager
{
friend class GameEngine;

public:
    GameManager();

private:
    void newGame();
    void updateStats();

    bool timeout();
    void decTimer(float);
    float calDeltaTime();

    bool paused;
    bool acceptInput;
    int score;

    const float initTimerVal;
    float timerVal;
    sf::Clock clock;    
};
