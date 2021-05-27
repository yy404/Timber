#pragma once
#include <vector>
#include <deque>
#include "Actor.hpp"

class Tree: public Actor
{
public:
	enum class Side { LEFT, RIGHT, NONE }; // Indicate which side of the tree

public:
	Tree(float fWindowWidth);
	
	void initialise();
	void fillBranches(int iSeed);

	void chop(Side sideOfTree, float fLogPositionY);
	Side getBottomBranchSide();

	virtual void update(float fTimeDelta) override;

private:
	Actor m_actorLog;
	float m_fPositionX;
	float m_fLogSpeedX;
	float m_fLogSpeedY;

	std::vector<Actor> m_vectorActorbranch;
	std::deque<Side> m_dequeBranchSide;
	const int m_kiBranchNum;
	const float m_kfBranchDistanceX;
	const float m_kfBranchDistanceY;

	Side newBranchSide();
};