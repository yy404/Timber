#include "GameEngine.hpp"

GameEngine::GameEngine(): 
    windowWidth(1920.0f), windowHeight(1080.0f), 
    gameUI(windowWidth, windowHeight), 
    tree(windowWidth), background("graphics/background.png")
{
    // Create a game window
    window.create(sf::VideoMode(windowWidth, windowHeight), "Game Window");
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
    // Handle event input
    sf::Event event;
    while (window.pollEvent(event)) // Must poll event to show the window
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
    
    // Handle menu input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        gameManager.newGame();
        gameUI.updateMessage("Press Space To Score!");
        gameUI.updateScore(gameManager.score);
    }
    
    // Handle player input
    if (gameManager.acceptInput && !gameManager.paused)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            gameManager.score++;
            gameUI.updateScore(gameManager.score);
            gameManager.acceptInput = false;
            tree.chop();
        }
    }
}

void GameEngine::update()
{
    if (!gameManager.paused)
    {
        // Update timer
        float deltaTime = gameManager.calDeltaTime();
        gameManager.decTimer(deltaTime);
        gameUI.updateTimer(gameManager.timerVal);
        Actor::updateActors(deltaTime);
        
        // Check if game over
        if (gameManager.checkEnd())
        {
            gameUI.updateMessage("Press Enter To Start!");
            gameManager.paused = true;
        }
    }
}

void GameEngine::draw()
{
    window.clear();
    Actor::drawActors(window);
    gameUI.drawUI(window);
    window.display();
}
