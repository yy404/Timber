#include "Actor.hpp"

// Set resourcePath() as an empty string if not using Xcode
#ifndef RESOURCE_PATH_HPP
#define resourcePath() ""
#endif

// Define a static vector to record all actors
std::vector<Actor*> Actor::actorPtrVector;

Actor::Actor(std::string spritePath) : speedX(0.0f), speedY(0.0f), isHidden(false)
{
    // Set the sprite given the full path of a texture 
    std::string fullPath = resourcePath() + spritePath;
    if (texture.loadFromFile(fullPath))
    {
        sprite.setTexture(texture);
    }
    else
    {
        // To handle the failure of loading texture
    }

    // Record the pointer of this actor
    Actor::actorPtrVector.push_back(this);
}

Actor::~Actor()
{
    //vector<Actor*>::iterator it;
    //it = actorPtrVector.find(this);
    //Actor::actorPtrVector.erase(it);
}

Actor::Actor(const Actor& other): 
    sprite(other.texture), texture(other.texture), 
    speedX(other.speedX), speedY(other.speedY), isHidden(other.isHidden)
{
    // Record the pointer of this actor
    Actor::actorPtrVector.push_back(this);
}

const sf::Sprite& Actor::getSprite() const
{
    return sprite;
}

void Actor::setOrigin(float xRatio, float yRatio)
{
    // To handle invalid input values

    // Calculate the new orgin based on the input values
    sf::FloatRect textRect = sprite.getLocalBounds();
    float xOrigin = textRect.left + (xRatio * textRect.width);
    float yOrigin = textRect.top + (yRatio * textRect.height);

    sprite.setOrigin(xOrigin, yOrigin);
}

void Actor::setRotation(float degreeVal)
{
    sprite.setRotation(degreeVal);
}

void Actor::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

void Actor::setVelocity(float x, float y)
{
    speedX = x;
    speedY = y;
}

void Actor::setHidden(bool inputBool)
{
    isHidden = inputBool;
}

void Actor::update(float deltaTime)
{
    // Update the position given current velocity and elapsed time
    if (speedX != 0.0f || speedY != 0.0f)
    {
        float newPositionX = sprite.getPosition().x + (speedX * deltaTime);
        float newPositionY = sprite.getPosition().y + (speedY * deltaTime);
        sprite.setPosition(newPositionX, newPositionY);
    }
}

void Actor::updateActors(float deltaTime)
{
    // Update the position of all actors
    for (auto actorPtr : Actor::actorPtrVector)
    {
        if (actorPtr != nullptr)
        {
            actorPtr->update(deltaTime);
        }
        else
        {
            // To handle a null pointer
        }
    }
}

void Actor::drawActors(sf::RenderWindow& window)
{
    // Draw the sprite of all actors
    for (auto actorPtr : Actor::actorPtrVector)
    {
        if (actorPtr != nullptr)
        {
            if (!actorPtr->isHidden)
            {
                window.draw(actorPtr->getSprite());
            }
        }
        else
        {
            // To handle a null pointer
        }
    }
}
