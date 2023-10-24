#pragma once

#include "iPlayer.h"

class iPlayerFactory
{
public:
	virtual ~iPlayerFactory() {};
	virtual iPlayer* CreatePlayer() = 0;
};

