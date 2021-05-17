#include "Player.hpp"

Player::Player(float windowWidth) : Actor("graphics/player.png"),
    centrePositionX(0.5f * windowWidth), playerPositionY(720.0f), ripPositionY(860.0f),
    distanceToTree(310.0f), distanceToAxeX(120.0f), distanceToAxeY(110.0f),
    playerSide(Side::LEFT), axe("graphics/axe.png"), rip("graphics/rip.png")
{
    setOrigin(0.5f, 0.0f);
    setPosition(centrePositionX - distanceToTree, playerPositionY);

    axe.setOrigin(0.5f, 0.0f);
    axe.setHidden(true);

    rip.setOrigin(0.5f, 0.0f);
    rip.setPosition(centrePositionX - distanceToTree, ripPositionY);
    rip.setHidden(true);
}

void Player::move(Side sideOfTree)
{
    playerSide = sideOfTree;
}

void Player::chop(Tree& tree)
{
    tree.chop(playerSide, playerPositionY);
    axe.setHidden(false);
}

void Player::update(float deltaTime)
{
    // Not actually using deltaTime for now

    if (playerSide == Side::LEFT)
    {
        float playerPositionX = centrePositionX - distanceToTree;
        setPosition(playerPositionX, playerPositionY);
        axe.setPosition(playerPositionX + distanceToAxeX, playerPositionY + distanceToAxeY);
    }
    else // The right side
    {
        float playerPositionX = centrePositionX + distanceToTree;
        setPosition(playerPositionX, playerPositionY);
        axe.setPosition(playerPositionX - distanceToAxeX, playerPositionY + distanceToAxeY);
    }
}

bool Player::isSquished(Tree& tree)
{
    return (tree.getBottomBranchSide() == playerSide);
}

void Player::hideAxe()
{
    axe.setHidden(true);
}

void Player::displayRIP(bool ifDisplayRIP)
{
    setHidden(ifDisplayRIP);
    rip.setHidden(!ifDisplayRIP);
}