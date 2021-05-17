#include "GameManager.hpp"

GameManager::GameManager() : paused(true), acceptInput(false), score(0), initTimerVal(6.0f), timerVal(initTimerVal)
{
}

void GameManager::newGame()
{
    paused = false;
    acceptInput = true;
    score = 0;
    timerVal = initTimerVal;
    clock.restart();
}

bool GameManager::timeout()
{
    return timerVal <= 0.0f;
}

void GameManager::decTimer(float deltaTime)
{
    timerVal -= deltaTime;
    if (timerVal < 0.0f)
    {
        timerVal = 0.0f;
    }
}

float GameManager::calDeltaTime()
{
    // Get the delta time and reset the timer
    sf::Time dt = clock.restart();
    return dt.asSeconds();
}

void GameManager::updateStats()
{
    score++;
    // Add bonus time by the given formula
    timerVal += (2.0f / score) + .15f;
}
