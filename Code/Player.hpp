#pragma once

#include "Actor.hpp"
#include "Tree.hpp"

enum class Side; // Declare the side class defined in "Tree.hpp"

class Player : public Actor
{
public:
	Player(float);
	void move(Side);
	void chop(Tree&);

	bool isSquished(Tree&);
	void hideAxe();
	void displayRIP(bool);

	virtual void update(float) override;

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