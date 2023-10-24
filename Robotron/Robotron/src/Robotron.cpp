#include "Robotron.h"
#include "Player/AbstractFactory/PlayerFactory.h"

void Robotron::SetUp()
{
#pragma region Player

	iPlayerFactory* playerFactory = new PlayerFactory();

	iPlayer* player =  playerFactory->CreateBasePlayer();

	entityManager.AddEntity("Player", (Entity*)player);

#pragma endregion

#pragma region EntityManager
	entityManager.AddToRenderer(renderer);

	entityManager.Start();
#pragma endregion
	
}

void Robotron::PreRender()
{
}

void Robotron::PostRender()
{
	entityManager.Update();
}

void Robotron::ProcessInput(GLFWwindow* window)
{
}

void Robotron::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
}

void Robotron::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
