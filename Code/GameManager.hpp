#pragma once
#include <SFML/Graphics.hpp>

enum class State { PAUSE, RUN, WAIT }; // Indicate the current game state

class GameManager
{
public:
    GameManager();

    void initStats();
    void updateStats();

    bool timeout();
    void decTimer(float fTimeDelta);
    float calDeltaTime();

    int getScore();
    float getTimerVal();

    void setState(State stateNew);
    State getState();

private:
    int m_iScore;
    State m_state;

    const float m_kfTimerInit; 
    float m_fTimer;
    sf::Clock m_clock;
};
