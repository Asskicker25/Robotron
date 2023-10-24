#pragma once

#include "iPlayerFactory.h"

class PlayerFactory : public iPlayerFactory
{
public:

	iPlayer* CreateBasePlayer() override;

	// Inherited via iPlayerFactory
	iPlayer* CreateFastPlayer() override;
};

