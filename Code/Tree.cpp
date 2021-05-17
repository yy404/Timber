#include "Tree.hpp"

Tree::Tree(float windowWidth) : Actor("graphics/tree.png"), 
    log("graphics/log.png"), logSpeedX(5000.0f), logSpeedY(1500.0f),
    NUM_BRANCHES(6), BRANCH_DIST_X(360.0f), BRANCH_DIST_Y(150.0f)
{
    treePositionX = 0.5f * windowWidth;

    setOrigin(0.5f, 0.0f);
    setPosition(treePositionX, 0.0f);

    log.setOrigin(0.5f, 0.0f);
    log.setHidden(true);

    branches.reserve(NUM_BRANCHES);
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches.emplace_back("graphics/branch.png");
        branches[i].setOrigin(0.5f, 0.5f);
        branches[i].setHidden(true);
    }
}

void Tree::chop(Side sideOfTree, float logPositionY)
{
    // The log velocity towards the x-axis positive direction if standing on the left side (vice versa)
    int xDirection = (sideOfTree == Side::LEFT) ? 1 : -1;
    // The log velocity always towards the negative direction of y-axis
    int yDirection = -1;

    // The log is flying from its initial position
	log.setPosition(treePositionX, logPositionY);
    log.setHidden(false);
	log.setVelocity(xDirection * logSpeedX, yDirection * logSpeedY);

    branchPositions.pop_front();
}

void Tree::update(float deltaTime)
{
    // Deactivate the log if it's out of the screen
    if (log.getSprite().getPosition().x < 0.0f * treePositionX ||
        log.getSprite().getPosition().x > 2.0f * treePositionX)
    {
        log.setHidden(true);
        log.setVelocity(0.0f, 0.0f);
    }

    // update the branch sprites
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        float height = static_cast<float>(NUM_BRANCHES-1-i) * BRANCH_DIST_Y;

        if (branchPositions[i] == Side::LEFT)
        {
            // Move the sprite to the left side
            branches[i].setPosition(treePositionX - BRANCH_DIST_X, height);
            // Flip the sprite round the other way
            branches[i].setRotation(180);
            branches[i].setHidden(false);
        }
        else if (branchPositions[i] == Side::RIGHT)
        {
            // Move the sprite to the right side
            branches[i].setPosition(treePositionX + BRANCH_DIST_X, height);
            // Set the sprite rotation to normal
            branches[i].setRotation(0);
            branches[i].setHidden(false);
        }
        else
        {
            // Hide the branch
            branches[i].setHidden(true);
        }
    }
}

Side Tree::newBranchSide()
{
    // 20% LEFT, 20% RIGHT, 60% NONE
    int r = (rand() % 5);
    Side newSide;
    switch (r) {
    case 0:
        newSide = Side::LEFT;
        break;
    case 1:
        newSide = Side::RIGHT;
        break;
    default:
        newSide = Side::NONE;
        break;
    }
    return newSide;
}

void Tree::fillBranches(int seed)
{
    srand((int)time(NULL) + seed);

    // The bottom one is always NONE when filling an empty tree.
    if (branchPositions.empty())
    {
        branchPositions.push_back(Side::NONE);
    }

    while (branchPositions.size() < NUM_BRANCHES)
    {
        branchPositions.push_back(newBranchSide());
    }
}

void Tree::initialise()
{
    branchPositions.clear();
    
    // Using seed 0 for initialisation
    fillBranches(0);

    log.setHidden(true);
    log.setVelocity(0.0f, 0.0f);
}

Side Tree::getBottomBranchSide()
{
    return branchPositions.front();
}
