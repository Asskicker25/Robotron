#pragma once

#include <vector>
#include "../AI/Enemies/BaseEnemy.h"
#include "Score.h"

class PlayerController;
class BaseBullet;

class GameMediator
{
private:
	std::vector<BaseEnemy* > listOfEnemies;
	std::vector<BaseBullet* > listOfBullets;


	Score* score;
	PlayerController* playerController;

public:

	void AddEnemy(BaseEnemy* enemy);
	void RemoveEnemy(BaseEnemy* enemy);

	void AddBullet(BaseBullet* bullet);
	void RemoveBullet(BaseBullet* bullet);

	void AssignScore(Score* score);
	void AssignPlayerController(PlayerController* playerController);
	
	void UpdatePlayerPosition(float posX, float posY);
	void OnPlayerDead();

	void AddScore(int score);
};

