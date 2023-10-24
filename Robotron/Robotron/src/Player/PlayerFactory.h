#pragma once

#include "iPlayerFactory.h"

class PlayerFactory : public iPlayerFactory
{
public:

	iPlayer* CreatePlayer() override;

};

