#include "PlayerController.h"

void PlayerController::AssignPlayer(BasePlayer* player)
{
	this->player = player;
	phyObj = player->phyObj;
}

void PlayerController::OnKeyPressed(const int& key)
{

#pragma region Movement

	if (key == GLFW_KEY_A)
	{
		if (currentVelocity.x >= 0.0f)
		{
			currentVelocity.x = -player->speed;
		}
		else
		{
			currentVelocity.x = -player->speed;
		}
	}

	if (key == GLFW_KEY_D)
	{
		if (currentVelocity.x <= 0.0f)
		{
			currentVelocity.x = player->speed;
		}
		else
		{
			currentVelocity.x = player->speed;
		}
	}

	if (key == GLFW_KEY_W)
	{
		if (currentVelocity.y <= 0.0f)
		{
			currentVelocity.y = player->speed;
		}
		else
		{
			currentVelocity.y = player->speed;
		}
	}

	if (key == GLFW_KEY_S)
	{
		if (currentVelocity.y >= 0.0f)
		{
			currentVelocity.y = -player->speed;
		}
		else
		{
			currentVelocity.y = -player->speed;
		}
	}
#pragma endregion

#pragma region Shoot

	if (key == GLFW_KEY_J)
	{
		player->Shoot();
	}
#pragma endregion

}

void PlayerController::OnKeyReleased(const int& key)
{

#pragma region Movement
	if (key == GLFW_KEY_A)
	{
		if (currentVelocity.x < 0.0f)
		{
			currentVelocity.x = 0.0f;
		}
	}

	if (key == GLFW_KEY_D)
	{
		if (currentVelocity.x > 0.0f)
		{
			currentVelocity.x = 0.0f;
		}
	}

	if (key == GLFW_KEY_W)
	{
		if (currentVelocity.y > 0.0f)
		{
			currentVelocity.y = 0.0f;
		}
	}

	if (key == GLFW_KEY_S)
	{
		if (currentVelocity.y < 0.0f)
		{
			currentVelocity.y = 0.0f;
		}
	}
#pragma endregion

}

void PlayerController::OnKeyHeld(const int& key)
{
}

void PlayerController::Start()
{
	InputManager::GetInstance().AddListener(this);
}

void PlayerController::Update(float deltaTime)
{
	player->UpdateVelocity(currentVelocity);
}

void PlayerController::AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine)
{
}

void PlayerController::RemoveFromRendererAndPhysics(Renderer& renderer, PhysicsEngine& physicsEngine)
{
}

