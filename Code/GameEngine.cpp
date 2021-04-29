#include "GameEngine.hpp"

GameEngine::GameEngine()
{
    // Get the screen resolution
    float width = sf::VideoMode::getDesktopMode().width;
    float height = sf::VideoMode::getDesktopMode().height;
    
    // Create the main window
    window.create(sf::VideoMode(width,height), "Timberman Game", sf::Style::Fullscreen);
}

void GameEngine::run()
{
    // Start the game loop
    while (window.isOpen())
    {
        input();
        update();
        draw();
    }
}

void GameEngine::input()
{
    // handle event input
    sf::Event event;
    while (window.pollEvent(event)) // must poll event to show the window
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
        }
        
        // Key released: listen for key presses again
        if (event.type == sf::Event::KeyReleased)
        {
            gameManager.acceptInput = true;
        }
    }
    
    // handle menu input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        gameManager.newGame();
        gameUI.updateMessage("Press Space To Score");
        gameUI.updateScore(gameManager.score);
    }
    
    // handle player input
    if (gameManager.acceptInput && !gameManager.paused)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            gameManager.score++;
            gameUI.updateScore(gameManager.score);
            gameManager.acceptInput = false;
        }
    }
}

void GameEngine::update()
{
    if (!gameManager.paused)
    {
        // update timer
        float deltaTime = gameManager.calDeltaTime();
        gameManager.decTimer(deltaTime);
        gameUI.updateTimer(gameManager.timerVal);
        
        // check if game over
        if (gameManager.checkEnd())
        {
            gameUI.updateMessage("Press Enter To Start");
            gameManager.paused = true;
        }
    }
}

void GameEngine::draw()
{
    window.clear();
    gameUI.drawUI(window);
    window.display();
}
