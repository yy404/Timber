#pragma once

#include "Actor.hpp"
#include "Tree.hpp"

enum class Side; // Declare the side class defined in "Tree.hpp"

class Player : public Actor
{
public:
	Player(float windowWidth);
	void move(Side sideOfTree);
	void chop(Tree& tree);

	bool isSquished(Tree& tree);
	void hideAxe();
	void displayRIP(bool ifDisplayRIP);

	virtual void update(float deltaTime) override;

private:

	float centrePositionX;
	float playerPositionY;
	float ripPositionY;

	float distanceToTree;
	float distanceToAxeX;
	float distanceToAxeY;

	Side playerSide;

	Actor axe;
	Actor rip;
};