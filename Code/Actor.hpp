#pragma once
#include <SFML/Graphics.hpp>
#include <vector> // Using a vector to record all actors

// In case of using Xcode
#ifdef XCODE_VERSION
#include "ResourcePath.hpp"
#endif

class Actor
{
public:
    Actor(std::string spritePath);
    ~Actor();
    Actor(const Actor& other);

    const sf::Sprite& getSprite() const;

    void setOrigin(float xRatio, float yRatio);
    void setRotation(float degreeVal);
    void setPosition(float x, float y);
    void setVelocity(float x, float y);
    void setHidden(bool ifSetHidden);

    virtual void update(float deltaTime);

    static void updateActors(float deltaTime);
    static void drawActors(sf::RenderWindow& window);

private:
    sf::Sprite sprite;
    sf::Texture texture;

    float speedX;
    float speedY;

    bool isHidden;

    static std::vector<Actor*> actorPtrVector;
};