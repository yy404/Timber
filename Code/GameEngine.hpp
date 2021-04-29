#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameUI.hpp"
#include "GameManager.hpp"

class GameEngine
{
public:
    GameEngine();
    void run();
    
private:
    void input();
    void update();
    void draw();
    
    sf::RenderWindow window;
    GameUI gameUI;
    GameManager gameManager;
};
