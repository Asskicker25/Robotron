#include "PlayerFactory.h"
#include "../Player.h"
#include "../Builder/PlayerBuilder.h"

BasePlayer* PlayerFactory::CreateBasePlayer()
{
	PlayerBuilder playerBuilder;
	
	return playerBuilder.SetMaxHealth(100.0f).SetSpeed(5.0f).BuildPlayer();
}

BasePlayer* PlayerFactory::CreateFastPlayer()
{
	PlayerBuilder playerBuilder;
	return playerBuilder.SetMaxHealth(100.0f).SetSpeed(10.0f).BuildPlayer();
}
