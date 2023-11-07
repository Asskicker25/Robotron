#pragma once

#include <vector>
#include "../Enemies/BaseEnemy.h"
#include "Score.h"

class GameMediator
{
private:
	std::vector<BaseEnemy* > listOfEnemies;

	Score* score;

public:

	void AddEnemy(BaseEnemy* enemy);
	void RemoveEnemy(BaseEnemy* enemy);

	void AssignScore(Score* score);
	
	void UpdatePlayerPosition(float posX, float posY);
	void OnPlayerDead();

	void AddScore(int score);
};

