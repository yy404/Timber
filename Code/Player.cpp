#include "Player.hpp"

Player::Player(float fWindowWidth) : Actor("graphics/player.png"),
    m_fCentrePositionX(0.5f * fWindowWidth), m_fPlayerPositionY(720.0f), m_fRipPositionY(860.0f),
    m_fTreeDistanceX(310.0f), m_fAxeDistanceX(120.0f), m_fAxeDistanceY(110.0f),
    m_sidePlayer(Side::LEFT), m_actorAxe("graphics/axe.png"), m_actorRIP("graphics/rip.png")
{
    setOrigin(0.5f, 0.0f);
    setPosition(m_fCentrePositionX - m_fTreeDistanceX, m_fPlayerPositionY);

    m_actorAxe.setOrigin(0.5f, 0.0f);
    m_actorAxe.setHidden(true);

    m_actorRIP.setOrigin(0.5f, 0.0f);
    m_actorRIP.setPosition(m_fCentrePositionX - m_fTreeDistanceX, m_fRipPositionY);
    m_actorRIP.setHidden(true);
}

void Player::move(Side sideOfTree)
{
    m_sidePlayer = sideOfTree;
}

void Player::chop(Tree& tree)
{
    tree.chop(m_sidePlayer, m_fPlayerPositionY);
    m_actorAxe.setHidden(false);
}

void Player::update(float fTimeDelta)
{
    // Not actually using deltaTime for now

    if (m_sidePlayer == Side::LEFT)
    {
        float fPositionX = m_fCentrePositionX - m_fTreeDistanceX;
        setPosition(fPositionX, m_fPlayerPositionY);
        m_actorAxe.setPosition(fPositionX + m_fAxeDistanceX, m_fPlayerPositionY + m_fAxeDistanceY);
    }
    else // The right side
    {
        float fPositionX = m_fCentrePositionX + m_fTreeDistanceX;
        setPosition(fPositionX, m_fPlayerPositionY);
        m_actorAxe.setPosition(fPositionX - m_fAxeDistanceX, m_fPlayerPositionY + m_fAxeDistanceY);
    }
}

bool Player::isSquished(Tree& tree)
{
    return (tree.getBottomBranchSide() == m_sidePlayer);
}

void Player::hideAxe()
{
    m_actorAxe.setHidden(true);
}

void Player::displayRIP(bool bDisplayRIP)
{
    // Show a gravestone and hide the player if ture
    setHidden(bDisplayRIP);
    m_actorRIP.setHidden(!bDisplayRIP);
}