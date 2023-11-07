#include "Robotron.h"
#include "Player/AbstractFactory/PlayerFactory.h"
#include "InputManager/InputManager.h"
#include "Player/Builder/PlayerBuilder.h"
#include "Player/PlayerController.h"
#include "Enemies/EnemiesManager.h"
#include "Level/Border.h"
#include "Level/GameMediator.h"
#include "Level/Score.h"

void Robotron::SetUp()
{

#pragma region Physics Settings

	physicsEngine.gravity.y = 0;
	physicsEngine.fixedStepTime = 0.01f;

#pragma endregion


#pragma region Camera

	stopKeyCallback = true;
	stopMouseCallback = true;

	SetBackgroundColor(glm::vec3(0.1f));

	cameraPos = glm::vec3(0.0f, 1.0f, 20.0f);

#pragma endregion

#pragma region Light

	Model* dirLightModel = new Model ("Assets/Models/DefaultSphere.fbx", false, false);
	dirLightModel->transform.SetScale(glm::vec3(0.05f));
	dirLightModel->isActive = false;

	Light* dirLight = new Light(dirLightModel, Directional);

	renderer.AddModel(dirLightModel,&lightShader);
	lightManager.AddLight(dirLight);

	lightManager.AddShader(defShader);
	
#pragma endregion

	EntityManager::GetInstance().AddToRendererAndPhysics(&renderer, &defShader, &physicsEngine);

#pragma region Level

	Border* border = new Border();

	GameMediator* gameMediator = new GameMediator();

	Score* score = new Score();
	
	gameMediator->AssignScore(score);

#pragma endregion

#pragma region Player

	PlayerFactory* playerFactory = new PlayerFactory();

	BasePlayer* player =  playerFactory->CreateBasePlayer();
	player->AssignGameMediator(gameMediator);

	PlayerController* playerController = new PlayerController();
	playerController->AssignPlayer(player);

#pragma endregion

#pragma region Enemies

	EnemiesManager* enemiesManager = new EnemiesManager(gameMediator);

#pragma endregion

#pragma region EntityManager


	EntityManager::GetInstance().Start();

#pragma endregion
	
}

void Robotron::PreRender()
{
}

void Robotron::PostRender()
{
	EntityManager::GetInstance().Update(deltaTime);
	physicsEngine.Update(deltaTime);
}

void Robotron::ProcessInput(GLFWwindow* window)
{
}

void Robotron::KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods)
{
	if (action == GLFW_PRESS)
	{
		InputManager::GetInstance().OnKeyPressed(key);
	}
	else if (action == GLFW_RELEASE)
	{
		InputManager::GetInstance().OnKeyReleased(key);
	}
	else if (action == GLFW_REPEAT)
	{
		InputManager::GetInstance().OnKeyHeld(key);
	}
}

void Robotron::MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods)
{
}
