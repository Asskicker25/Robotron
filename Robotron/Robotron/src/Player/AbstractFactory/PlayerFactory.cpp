#include "PlayerFactory.h"
#include "../Player.h"
#include "../Builder/PlayerBuilder.h"

iPlayer* PlayerFactory::CreateBasePlayer()
{
	PlayerBuilder playerBuilder;

	playerBuilder.SetMaxHealth(100.0f);
	playerBuilder.SetSpeed(1.0f);

	return playerBuilder.BuildPlayer();
}

iPlayer* PlayerFactory::CreateFastPlayer()
{
	PlayerBuilder playerBuilder;

	playerBuilder.SetMaxHealth(100.0f);
	playerBuilder.SetSpeed(3.0f);

	return playerBuilder.BuildPlayer();
}
