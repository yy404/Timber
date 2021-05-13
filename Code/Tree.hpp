#pragma once

#include "Actor.hpp"

class Tree: public Actor
{
public:
	Tree(float);
	void chop();
	void update(float) override;
private:
	Actor log;

	float treePositionX;
	float logPositionY;
	float logSpeedX;
	float logSpeedY;
};