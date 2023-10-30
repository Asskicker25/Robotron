#pragma once

#include "../BasePlayer.h"

class PlayerFactory 
{
public:

	BasePlayer* CreateBasePlayer();
	BasePlayer* CreateFastPlayer();
};

