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
    Actor(std::string);
    ~Actor();
    Actor(const Actor&);

    const sf::Sprite& getSprite() const;

    void setOrigin(float, float);
    void setRotation(float);
    void setPosition(float, float);
    void setVelocity(float, float);
    void setHidden(bool);

    virtual void update(float);

    static void updateActors(float);
    static void drawActors(sf::RenderWindow&);

private:
    sf::Sprite sprite;
    sf::Texture texture;

    float speedX;
    float speedY;

    bool isHidden;

    static std::vector<Actor*> actorPtrVector;
};