#include "GameManager.hpp"

GameManager::GameManager(): timerValMax(6.0f), paused(true), acceptInput(false), score(0), timerVal(timerValMax)
{
}

void GameManager::newGame()
{
    timerVal = timerValMax;
    paused = false;
    acceptInput = true;
    score = 0;
    clock.restart();
}

bool GameManager::checkEnd()
{
    // End game if timer expires
    return timerVal <= 0;
}

void GameManager::decTimer(float delta)
{
    timerVal -= delta;
    if (timerVal < 0)
    {
        timerVal = 0;
    }
}

float GameManager::calDeltaTime()
{
    // Get the delta time and reset the timer
    sf::Time dt = clock.restart();
    return dt.asSeconds();
}
