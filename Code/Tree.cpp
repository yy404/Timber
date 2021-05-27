#include "Tree.hpp"

Tree::Tree(float fWindowWidth) : Actor("graphics/tree.png"),
    m_actorLog("graphics/log.png"), m_fLogSpeedX(5000.0f), m_fLogSpeedY(1500.0f),
    m_kiBranchNum(6), m_kfBranchDistanceX(360.0f), m_kfBranchDistanceY(150.0f)
{
    m_fPositionX = 0.5f * fWindowWidth;

    setOrigin(0.5f, 0.0f);
    setPosition(m_fPositionX, 0.0f);

    m_actorLog.setOrigin(0.5f, 0.0f);
    m_actorLog.setHidden(true);

    m_vectorActorbranch.reserve(m_kiBranchNum);
    for (int i = 0; i < m_kiBranchNum; i++)
    {
        m_vectorActorbranch.emplace_back("graphics/branch.png");
        m_vectorActorbranch[i].setOrigin(0.5f, 0.5f);
        m_vectorActorbranch[i].setHidden(true);
    }
}

void Tree::chop(Side sideOfTree, float fLogPositionY)
{
    // The log velocity towards the x-axis positive direction if standing on the left side (vice versa)
    int iDirectionX = (sideOfTree == Side::LEFT) ? 1 : -1;
    // The log velocity always towards the negative direction of y-axis
    int iDirectionY = -1;

    // The log is flying from its initial position
    m_actorLog.setPosition(m_fPositionX, fLogPositionY);
    m_actorLog.setHidden(false);
    m_actorLog.setVelocity(iDirectionX * m_fLogSpeedX, iDirectionY * m_fLogSpeedY);

    m_dequeBranchSide.pop_front();
}

void Tree::update(float fTimeDelta)
{
    // Deactivate the log if it's out of the screen
    if (m_actorLog.getSprite().getPosition().x < 0.0f * m_fPositionX ||
        m_actorLog.getSprite().getPosition().x > 2.0f * m_fPositionX)
    {
        m_actorLog.setHidden(true);
        m_actorLog.setVelocity(0.0f, 0.0f);
    }

    // update the branch sprites
    for (int i = 0; i < m_kiBranchNum; i++)
    {
        float fHeight = static_cast<float>(m_kiBranchNum-1-i) * m_kfBranchDistanceY;

        if (m_dequeBranchSide[i] == Side::LEFT)
        {
            // Move the sprite to the left side
            m_vectorActorbranch[i].setPosition(m_fPositionX - m_kfBranchDistanceX, fHeight);
            // Flip the sprite round the other way
            m_vectorActorbranch[i].setRotation(180);
            m_vectorActorbranch[i].setHidden(false);
        }
        else if (m_dequeBranchSide[i] == Side::RIGHT)
        {
            // Move the sprite to the right side
            m_vectorActorbranch[i].setPosition(m_fPositionX + m_kfBranchDistanceX, fHeight);
            // Set the sprite rotation to normal
            m_vectorActorbranch[i].setRotation(0);
            m_vectorActorbranch[i].setHidden(false);
        }
        else
        {
            // Hide the branch
            m_vectorActorbranch[i].setHidden(true);
        }
    }
}

Tree::Side Tree::newBranchSide()
{
    // 20% LEFT, 20% RIGHT, 60% NONE
    int r = (rand() % 5);
    Side sideNew;
    switch (r) {
    case 0:
        sideNew = Side::LEFT;
        break;
    case 1:
        sideNew = Side::RIGHT;
        break;
    default:
        sideNew = Side::NONE;
        break;
    }
    return sideNew;
}

void Tree::fillBranches(int iSeed)
{
    srand((int)time(NULL) + iSeed);

    // The bottom one is always NONE when filling an empty tree.
    if (m_dequeBranchSide.empty())
    {
        m_dequeBranchSide.push_back(Side::NONE);
    }

    while (m_dequeBranchSide.size() < m_kiBranchNum)
    {
        m_dequeBranchSide.push_back(newBranchSide());
    }
}

void Tree::initialise()
{
    m_dequeBranchSide.clear();
    
    // Using seed 0 for initialisation
    fillBranches(0);

    m_actorLog.setHidden(true);
    m_actorLog.setVelocity(0.0f, 0.0f);
}

Tree::Side Tree::getBottomBranchSide()
{
    return m_dequeBranchSide.front();
}
