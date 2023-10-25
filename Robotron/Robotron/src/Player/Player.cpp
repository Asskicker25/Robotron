#include "Player.h"
#include <Graphics/Debugger.h>
#include "../InputManager/InputManager.h"

void Player::SetMaxHealth(const float& maxHealth)
{
	this->maxHealth = maxHealth;
}

void Player::SetSpeed(const float& speed)
{
	this->speed = speed;
}

void Player::Shoot()
{
}

void Player::Start()
{
	InputManager::GetInstance().AddListener(this);
}

void Player::Update()
{
}

void Player::AddToRenderer(Renderer& renderer, Shader* shader)
{
	model.LoadModel("Assets/Models/Player/player1.ply");
	model.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	model.transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	model.transform.SetScale(glm::vec3(0.01f));

	renderer.AddModel(&model, shader);
}

void Player::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_A)
	{
		phyObject.velocity.x = -10.0f;
	}

	if (key == GLFW_KEY_D)
	{
		phyObject.velocity.x = 10.0f;
	}
}

void Player::OnKeyReleased(const int& key)
{
	if (key == GLFW_KEY_A)
	{
		phyObject.velocity.x = 0.0f;
	}

	if (key == GLFW_KEY_D)
	{
		phyObject.velocity.x = 0.0f;
	}

}

void Player::OnKeyHeld(const int& key)
{
	if (key == GLFW_KEY_A)
	{

	}
}

void Player::AddToPhysics(PhysicsEngine& physicsEngine)
{
	Debugger::Print("Player added to physics");

	phyObject.Initialize(&model, AABB, DYNAMIC);

	physicsEngine.AddPhysicsObject(&phyObject);
}

