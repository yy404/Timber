#include "Tree.hpp"

Tree::Tree(float windowWidth) : 
    Actor("graphics/tree.png"), log("graphics/log.png"), 
    logPositionY(720), logSpeedX(1000), logSpeedY(1500)
{
    treePositionX = 0.5f * windowWidth;

    this->setOrigin(0.5f, 0.0f);
    this->setPosition(treePositionX, 0.0f);

    log.setOrigin(0.5f, 0.0f);
    log.setPosition(treePositionX, logPositionY);
}

void Tree::chop()
{
    // The log is flying from its initial position
	log.setPosition(treePositionX, logPositionY);
	log.setVelocity(logSpeedX, -1 * logSpeedY);
}

void Tree::update(float deltaTime)
{
    // Reset the log if it's out of the screen
    if (log.getSprite().getPosition().x < 0 ||
        log.getSprite().getPosition().x > 2 * treePositionX)
    {
        log.setPosition(treePositionX, logPositionY);
        log.setVelocity(0, 0);
    }
}
