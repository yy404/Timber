#pragma once
#include <SFML/Graphics.hpp>

enum class State { PAUSE, RUN, WAIT }; // Indicate the current game state

class GameManager
{
public:
    GameManager();

    void newGame();
    void updateStats();

    bool timeout();
    void decTimer(float deltaTime);
    float calDeltaTime();

    int getScore();
    float getTimerVal();

    void setGameState(State currState);
    State getGameState();

private:
    int score;
    State gameState;

    const float initTimerVal;
    float timerVal;
    sf::Clock clock;
};
