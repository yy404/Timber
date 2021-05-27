#include "GameEngine.hpp"

GameEngine::GameEngine() : 
    m_fWindowWidth(1920.0f), m_fWindowHeight(1080.0f),
    m_gameUI(m_fWindowWidth, m_fWindowHeight),
    m_actorBackground("graphics/background.png"),
    m_actorTree(m_fWindowWidth), m_actorPlayer(m_fWindowWidth)
{
    // Create a game window
    m_window.create(sf::VideoMode(m_fWindowWidth, m_fWindowHeight), "Game Window");
}

void GameEngine::run()
{
    // Start the game loop
    while (m_window.isOpen())
    {
        input();
        update();
        draw();
    }
}

void GameEngine::input()
{
    // Handle event input
    sf::Event event;
    while (m_window.pollEvent(event)) // Must poll event to show the window
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }

        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_window.close();
            }
        }
        
        // Key released: listen for key presses again
        if (event.type == sf::Event::KeyReleased)
        {
            if (m_gameManager.getState() == GameManager::GameState::WAIT)
            {
                m_gameManager.setState(GameManager::GameState::RUN);
            }
            m_actorPlayer.hideAxe();
        }
    }
    
    // Handle menu input: start a new game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        m_gameManager.initStats();
        m_gameManager.setState(GameManager::GameState::WAIT);
        
        m_gameUI.updateMessage("");
        m_gameUI.updateScore(m_gameManager.getScore());

        m_actorTree.initialise();
        m_actorPlayer.displayRIP(false);
    }
    
    // Handle player input
    if (m_gameManager.getState() == GameManager::GameState::RUN)
    {
        bool bPlayerAct = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_actorPlayer.move(Tree::Side::RIGHT);
            bPlayerAct = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_actorPlayer.move(Tree::Side::LEFT);
            bPlayerAct = true;
        }

        if (bPlayerAct)
        {
            m_actorPlayer.chop(m_actorTree);
            m_actorTree.fillBranches(m_gameManager.getScore());

            m_gameManager.updateStats();
            m_gameUI.updateScore(m_gameManager.getScore());
            m_gameManager.setState(GameManager::GameState::WAIT);
        }
    }
}

void GameEngine::update()
{
    if (m_gameManager.getState() != GameManager::GameState::PAUSE)
    {
        // Update timer
        float fTimeDelta = m_gameManager.calDeltaTime();
        m_gameManager.decTimer(fTimeDelta);
        m_gameUI.updateTimer(m_gameManager.getTimerVal());
        Actor::updateActors(fTimeDelta);
        
        // Check if game over
        if (m_gameManager.timeout())
        {
            m_gameUI.updateMessage("Out of time!!");
            m_gameManager.setState(GameManager::GameState::PAUSE);
        }
        else if (m_actorPlayer.isSquished(m_actorTree))
        {
            m_gameUI.updateMessage("SQUISHED!!");
            m_gameManager.setState(GameManager::GameState::PAUSE);

            m_actorPlayer.displayRIP(true);
        }
    }
}

void GameEngine::draw()
{
    m_window.clear();
    Actor::drawActors(m_window);
    m_gameUI.drawUI(m_window);
    m_window.display();
}
