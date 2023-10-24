#pragma once

#include "iPlayerBuilder.h"
#include "../Player.h"

class PlayerBuilder : public iPlayerBuilder
{
private:
	Player* player;

public:
	PlayerBuilder();
	// Inherited via iPlayerBuilder
	void SetMaxHealth(const float& maxHealth) override;
	void SetSpeed(const float& speed) override;
	iPlayer* BuildPlayer() override;
};

