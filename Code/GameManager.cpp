#include "GameManager.hpp"

GameManager::GameManager() : m_iScore(0), m_state(GameState::PAUSE), m_kfTimerInit(6.0f), m_fTimer(m_kfTimerInit)
{
}

void GameManager::initStats()
{
    m_iScore = 0;
    m_fTimer = m_kfTimerInit;
    m_clock.restart();
}

void GameManager::updateStats()
{
    m_iScore++;
    // Add bonus time by the given formula
    m_fTimer += (2.0f / m_iScore) + .15f;
}

bool GameManager::timeout()
{
    return m_fTimer <= 0.0f;
}

void GameManager::decTimer(float fTimeDelta)
{
    m_fTimer -= fTimeDelta;
    if (m_fTimer < 0.0f)
    {
        m_fTimer = 0.0f;
    }
}

float GameManager::calDeltaTime()
{
    // Get the delta time and reset the timer
    sf::Time dt = m_clock.restart();
    return dt.asSeconds();
}

int GameManager::getScore()
{
    return m_iScore;
}

float GameManager::getTimerVal()
{
    return m_fTimer;
}

void GameManager::setState(GameState stateNew)
{
    m_state = stateNew;
}

GameManager::GameState GameManager::getState()
{
    return m_state;
}
