#include "Robotron.h"
#include "Player/Player.h"

void Robotron::SetUp()
{
	Entity* player = new Player();

	entityManager.AddEntity("Player", player);

	entityManager.AddToRenderer(renderer);

	entityManager.Start();
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
