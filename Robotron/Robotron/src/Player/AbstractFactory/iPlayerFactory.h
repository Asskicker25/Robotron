#pragma once

#include "../iPlayer.h"

class iPlayerFactory
{
public:
	virtual ~iPlayerFactory() {};
	virtual iPlayer* CreateBasePlayer() = 0;
	virtual iPlayer* CreateFastPlayer() = 0;
};

