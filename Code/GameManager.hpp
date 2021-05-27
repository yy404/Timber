#pragma once
#include <SFML/Graphics.hpp>

class GameManager
{
public:
    enum class GameState { PAUSE, RUN, WAIT };

public:
    GameManager();

    void initStats();
    void updateStats();

    bool timeout();
    void decTimer(float fTimeDelta);
    float calDeltaTime();

    int getScore();
    float getTimerVal();

    void setState(GameState stateNew);
    GameState getState();

private:
    int m_iScore;
    GameState m_state;

    const float m_kfTimerInit; 
    float m_fTimer;
    sf::Clock m_clock;
};
