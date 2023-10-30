#include "PlayerBuilder.h"

PlayerBuilder::PlayerBuilder()
{
    player = new Player();
}

PlayerBuilder& PlayerBuilder::SetMaxHealth(const float& maxHealth)
{
    player->SetMaxHealth(maxHealth);
    return *this;
}

PlayerBuilder& PlayerBuilder::SetSpeed(const float& speed)
{
    player->SetSpeed(speed);
    return *this;
}

BasePlayer* PlayerBuilder::BuildPlayer()
{
    return player;
}
