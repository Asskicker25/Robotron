#pragma once

#include "iPlayerBuilder.h"

class PlayerBuilder : public iPlayerBuilder
{

	// Inherited via iPlayerBuilder
	void SetMaxHealth() override;
	void SetSpeed() override;
	iPlayer* BuildPlayer() override;
};

