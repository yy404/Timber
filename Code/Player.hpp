#pragma once

#include "Actor.hpp"
#include "Tree.hpp"

enum class Side; // Declare the side class defined in "Tree.hpp"

class Player : public Actor
{
public:
	Player(float fWindowWidth);
	void move(Side sideOfTree);
	void chop(Tree& tree);

	bool isSquished(Tree& tree);
	void hideAxe();
	void displayRIP(bool bDisplayRIP);

	virtual void update(float fTimeDelta) override;

private:

	float m_fCentrePositionX;
	float m_fPlayerPositionY;
	float m_fRipPositionY;

	float m_fTreeDistanceX;
	float m_fAxeDistanceX;
	float m_fAxeDistanceY;

	Side m_sidePlayer;

	Actor m_actorAxe;
	Actor m_actorRIP;
};