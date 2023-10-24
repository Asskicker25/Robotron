#pragma once

#include "../iPlayer.h"

class iPlayerBuilder
{
public:
	virtual ~iPlayerBuilder() {};
	virtual void SetMaxHealth(const float& maxHealth) = 0;
	virtual void SetSpeed(const float& speed) = 0;

	virtual iPlayer* BuildPlayer() = 0;
};


