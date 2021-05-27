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
    Actor(std::string strSpritePath);
    virtual ~Actor();
    Actor(const Actor& krActorOther);

    const sf::Sprite& getSprite() const;

    void setOrigin(float fRatioX, float fRatioY);
    void setRotation(float fValDegree);
    void setPosition(float fPositionX, float fPositionY);
    void setVelocity(float fSpeedX, float fSpeedY);
    void setHidden(bool bIsHidden);

    virtual void update(float fTimeDelta);

    static void updateActors(float fTimeDelta);
    static void drawActors(sf::RenderWindow& window);

private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;

    float m_fSpeedX;
    float m_fSpeedY;

    bool m_bIsHidden;

    static std::vector<Actor*> sVectorActorPtr;
};