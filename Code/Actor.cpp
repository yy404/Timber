#include "Actor.hpp"

// Set resourcePath() as an empty string if not using Xcode
#ifndef RESOURCE_PATH_HPP
#define resourcePath() ""
#endif

// Define a static vector to record all actors
std::vector<Actor*> Actor::sVectorActorPtr;

Actor::Actor(std::string strSpritePath) : m_fSpeedX(0.0f), m_fSpeedY(0.0f), m_bIsHidden(false)
{
    // Set the sprite given the full path of a texture 
    std::string strFullPath = resourcePath() + strSpritePath;
    if (m_texture.loadFromFile(strFullPath))
    {
        m_sprite.setTexture(m_texture);
    }

    // Record the pointer of this actor
    Actor::sVectorActorPtr.push_back(this);
}

Actor::~Actor()
{
    for (auto it = Actor::sVectorActorPtr.begin(); it != Actor::sVectorActorPtr.end(); it++)
    {
        if (*it == this)
        {
            Actor::sVectorActorPtr.erase(it);
            break;
        }
    }
}

Actor::Actor(const Actor& krActorOther): 
    m_sprite(krActorOther.m_texture), m_texture(krActorOther.m_texture), 
    m_fSpeedX(krActorOther.m_fSpeedX), m_fSpeedY(krActorOther.m_fSpeedY), m_bIsHidden(krActorOther.m_bIsHidden)
{
    // Record the pointer of this actor
    Actor::sVectorActorPtr.push_back(this);
}

const sf::Sprite& Actor::getSprite() const
{
    return m_sprite;
}

void Actor::setOrigin(float fRatioX, float fRatioY)
{
    // Calculate the new orgin based on the input values
    sf::FloatRect textRect = m_sprite.getLocalBounds();
    float xOrigin = textRect.left + (fRatioX * textRect.width);
    float yOrigin = textRect.top + (fRatioY * textRect.height);

    m_sprite.setOrigin(xOrigin, yOrigin);
}

void Actor::setRotation(float fValDegree)
{
    m_sprite.setRotation(fValDegree);
}

void Actor::setPosition(float fPositionX, float fPositionY)
{
    m_sprite.setPosition(fPositionX, fPositionY);
}

void Actor::setVelocity(float fSpeedX, float fSpeedY)
{
    m_fSpeedX = fSpeedX;
    m_fSpeedY = fSpeedY;
}

void Actor::setHidden(bool bIsHidden)
{
    m_bIsHidden = bIsHidden;
}

void Actor::update(float fTimeDelta)
{
    // Update the position given current velocity and elapsed time
    if (m_fSpeedX != 0.0f || m_fSpeedY != 0.0f)
    {
        float newPositionX = m_sprite.getPosition().x + (m_fSpeedX * fTimeDelta);
        float newPositionY = m_sprite.getPosition().y + (m_fSpeedY * fTimeDelta);
        m_sprite.setPosition(newPositionX, newPositionY);
    }
}

void Actor::updateActors(float fTimeDelta)
{
    // Update the position of all actors
    for (auto pActor : Actor::sVectorActorPtr)
    {
        if (pActor != nullptr)
        {
            pActor->update(fTimeDelta);
        }
    }
}

void Actor::drawActors(sf::RenderWindow& window)
{
    // Draw the sprite of all actors
    for (auto pActor : Actor::sVectorActorPtr)
    {
        if (pActor != nullptr && !pActor->m_bIsHidden)
        {
            window.draw(pActor->getSprite());
        }
    }
}
