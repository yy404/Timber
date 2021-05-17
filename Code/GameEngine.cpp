#include "GameEngine.hpp"

GameEngine::GameEngine() : 
    windowWidth(1920.0f), windowHeight(1080.0f), 
    gameUI(windowWidth, windowHeight), 
    background("graphics/background.png"),
    tree(windowWidth), player(windowWidth)
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
            player.hideAxe();
        }
    }
    
    // Handle menu input: start a new game
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        gameManager.newGame();
        
        gameUI.updateMessage("");
        gameUI.updateScore(gameManager.score);

        tree.initialise();
        player.displayRIP(false);
    }
    
    // Handle player input
    if (gameManager.acceptInput && !gameManager.paused)
    {
        bool isMoved = false;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(Side::RIGHT);
            isMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(Side::LEFT);
            isMoved = true;
        }

        if (isMoved)
        {
            player.chop(tree);
            tree.fillBranches(gameManager.score);

            gameManager.updateStats();
            gameUI.updateScore(gameManager.score);
            gameManager.acceptInput = false;
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
        if (gameManager.timeout())
        {
            gameUI.updateMessage("Out of time!!");
            gameManager.paused = true;
        }
        else if (player.isSquished(tree))
        {
            gameUI.updateMessage("SQUISHED!!");
            gameManager.paused = true;

            player.displayRIP(true);
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
