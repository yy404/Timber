#pragma once
#include <SFML/Graphics.hpp>
#include "GameUI.hpp"
#include "GameManager.hpp"
#include "Actor.hpp"
#include "Tree.hpp"
#include "Player.hpp"

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
    float windowWidth;
    float windowHeight;

    GameUI gameUI;
    GameManager gameManager;

    Actor background;
    Tree tree;
    Player player;
};
