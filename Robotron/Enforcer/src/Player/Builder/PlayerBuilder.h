#pragma once

#include "BasePlayerBuilder.h"
#include "../Player.h"

class PlayerBuilder : public BasePlayerBuilder
{
private:
	Player* player;

public:
	PlayerBuilder();

	// Inherited via iPlayerBuilder
	PlayerBuilder& SetMaxHealth(const float& maxHealth) override;
	PlayerBuilder& SetSpeed(const float& speed) override;
	BasePlayer* BuildPlayer() override;
};

