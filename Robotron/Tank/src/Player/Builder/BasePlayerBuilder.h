#pragma once

#include "../BasePlayer.h"

class BasePlayerBuilder
{
public:
	virtual ~BasePlayerBuilder() {};

	virtual BasePlayerBuilder& SetMaxHealth(const float& maxHealth) = 0;
	virtual BasePlayerBuilder& SetSpeed(const float& speed) = 0;
	virtual BasePlayer* BuildPlayer() = 0;
};


