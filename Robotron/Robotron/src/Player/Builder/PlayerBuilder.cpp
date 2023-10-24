#include "PlayerBuilder.h"

PlayerBuilder::PlayerBuilder()
{
    player = new Player();
}

void PlayerBuilder::SetMaxHealth(const float& maxHealth)
{
    player->SetMaxHealth(maxHealth);
}

void PlayerBuilder::SetSpeed(const float& speed)
{
    player->SetSpeed(speed);
}

iPlayer* PlayerBuilder::BuildPlayer()
{
    return player;
}
