#include "PlayerFactory.h"
#include "Player.h"

iPlayer* PlayerFactory::CreatePlayer()
{
	return new Player();
}
