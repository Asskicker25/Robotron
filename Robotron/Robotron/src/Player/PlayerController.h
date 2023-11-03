#pragma once

#include "BasePlayer.h"
#include "../InputManager/InputManager.h"


class PlayerController : public iInputListener, public Entity
{

public:
	PlayerController();
	void AssignPlayer(BasePlayer* player);

private:
	BasePlayer* player;
	PhysicsObject* phyObj;

	glm::vec3 currentVelocity;

	// Inherited via iInputListener
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;

	


	// Inherited via Entity
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;

	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

