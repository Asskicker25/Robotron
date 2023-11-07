#include "GameMediator.h"
#include "../Player/PlayerController.h"

void GameMediator::AddEnemy(BaseEnemy* enemy)
{
	listOfEnemies.push_back(enemy);
}

void GameMediator::RemoveEnemy(BaseEnemy* enemy)
{
	listOfEnemies.erase(std::remove(listOfEnemies.begin(), listOfEnemies.end(), enemy), listOfEnemies.end());
}

void GameMediator::AssignScore(Score* score)
{
	this->score = score;
}

void GameMediator::AssignPlayerController(PlayerController* playerController)
{
	this->playerController = playerController;
}

void GameMediator::UpdatePlayerPosition(float posX, float posY)
{
	for (BaseEnemy* enemy : listOfEnemies)
	{
		enemy->MoveTowardsPlayerPosition(posX, posY);
	}
}

void GameMediator::OnPlayerDead()
{
	for (BaseEnemy* enemy : listOfEnemies)
	{
		enemy->OnPlayerDead();
	}

	playerController->OnPlayerDead();
}

void GameMediator::AddScore(int score)
{
	this->score->AddScore(score);
}
