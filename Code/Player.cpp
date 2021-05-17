#include "Player.hpp"

Player::Player(float windowWidth) : Actor("graphics/player.png"),
    centrePositionX(0.5f * windowWidth), playerPositionY(720.0f), ripPositionY(860.0f),
    distanceToTree(310.0f), distanceToAxeX(120.0f), distanceToAxeY(110.0f),
    playerSide(Side::LEFT), axe("graphics/axe.png"), rip("graphics/rip.png")
{
    this->setOrigin(0.5f, 0.0f);
    this->setPosition(centrePositionX - distanceToTree, playerPositionY);

    axe.setOrigin(0.5f, 0.0f);
    axe.setHidden(true);

    rip.setOrigin(0.5f, 0.0f);
    rip.setPosition(centrePositionX - distanceToTree, ripPositionY);
    rip.setHidden(true);
}

void Player::move(Side side)
{
    playerSide = side;
}

void Player::chop(Tree& tree)
{
    tree.chop(playerSide, playerPositionY);
    axe.setHidden(false);
}

void Player::update(float)
{
    if (playerSide == Side::LEFT)
    {
        this->setPosition(centrePositionX - distanceToTree, playerPositionY);
        axe.setPosition(centrePositionX - distanceToTree + distanceToAxeX, playerPositionY + distanceToAxeY);
    }
    else // The right side
    {
        this->setPosition(centrePositionX + distanceToTree, playerPositionY);
        axe.setPosition(centrePositionX + distanceToTree - distanceToAxeX, playerPositionY + distanceToAxeY);
    }
}

bool Player::isSquished(Tree& tree)
{
    if (tree.getBottomBranchSide() == playerSide)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Player::hideAxe()
{
    axe.setHidden(true);
}

void Player::displayRIP(bool inputBool)
{
    rip.setHidden(!inputBool);
    this->setHidden(inputBool);
}