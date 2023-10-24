#pragma once

#include "iPlayer.h"

class iPlayerBuilder
{
public:
	virtual ~iPlayerBuilder() {};
	virtual void SetMaxHealth() = 0;
	virtual void SetSpeed() = 0;

	virtual iPlayer* BuildPlayer() = 0;
};


