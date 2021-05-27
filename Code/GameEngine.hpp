#pragma once
#include <SFML/Graphics.hpp>
#include "GameUI.hpp"
#include "GameManager.hpp"
#include "Actor.hpp"
#include "Tree.hpp"
#include "Player.hpp"

enum class State; // Declare the State class defined in "GameManager.hpp"

class GameEngine
{
public:
    GameEngine();
    void run();
    
private:
    void input();
    void update();
    void draw();
    
    sf::RenderWindow m_window;
    float m_fWindowWidth;
    float m_fWindowHeight;

    GameUI m_gameUI;
    GameManager m_gameManager;

    Actor m_actorBackground;
    Tree m_actorTree;
    Player m_actorPlayer;
};
