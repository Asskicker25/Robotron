#pragma once

#include <vector>
#include "../Enemies/BaseEnemy.h"

class GameMediator
{
private:
	std::vector<BaseEnemy* > listOfEnemies;

public:

	void AddEnemy(BaseEnemy* enemy);
	void RemoveEnemy(BaseEnemy* enemy);
	
	void UpdatePlayerPosition(float posX, float posY);
	void OnPlayerDead();
};

