#pragma once
#include <vector>
#include <deque>
#include "Actor.hpp"

enum class Side { LEFT, RIGHT, NONE }; // Indicate which side of the tree

class Tree: public Actor
{
public:
	Tree(float windowWidth);
	
	void initialise();
	void fillBranches(int seed);

	void chop(Side sideOfTree, float logPositionY);
	Side getBottomBranchSide();

	virtual void update(float deltaTime) override;

private:
	Actor log;
	float treePositionX;
	float logSpeedX;
	float logSpeedY;

	std::vector<Actor> branches;
	std::deque<Side> branchPositions;
	const int NUM_BRANCHES;
	const float BRANCH_DIST_X;
	const float BRANCH_DIST_Y;

	Side newBranchSide();
};