#include "Robotron.h"
#include "Player/AbstractFactory/PlayerFactory.h"
#include "InputManager/InputManager.h"

void Robotron::SetUp()
{
#pragma region Physics Settings

	physicsEngine.gravity.y = 0;
	physicsEngine.fixedStepTime = 0.01f;

#pragma endregion


#pragma region Stop Free Cam

	stopKeyCallback = true;
	stopMouseCallback = true;
	
#pragma endregion

#pragma region Camera

	cameraPos = glm::vec3(0.0f, 1.0f, 10.0f);

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

#pragma region Player

	iPlayerFactory* playerFactory = new PlayerFactory();

	iPlayer* player =  playerFactory->CreateBasePlayer();

	entityManager.AddEntity("Player", (Entity*)player);

#pragma endregion

#pragma region EntityManager

	entityManager.AddToRenderer(renderer, &defShader);
	entityManager.AddToPhysics(physicsEngine);

	entityManager.Start();

#pragma endregion
	
}

void Robotron::PreRender()
{
}

void Robotron::PostRender()
{
	entityManager.Update();
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
