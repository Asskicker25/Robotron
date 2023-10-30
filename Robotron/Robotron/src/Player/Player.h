#pragma once
#include "../EntityManager/EntityManager.h"
#include "BasePlayer.h"

class Player : public BasePlayer
{
private:

	class Pimpl;
	Pimpl* pimpl;



public:
	Player();

	//Model* bulletPrefab;

	// Inherited via iPlayer
	void Shoot() override;
	void Start() override;
	void Update(float deltaTime) override;
	

	//Builder function
	void SetMaxHealth(const float& maxHealth) override;
	void SetSpeed(const float& speed) override;

	// Inherited via BasePlayer
	void UpdateVelocity(glm::vec3 velocity) override;
	void AddToRendererAndPhysics(Renderer& renderer, Shader* shader, PhysicsEngine& physicsEngine) override;
	void RemoveFromRenderer(Renderer& renderer) override;
	void RemoveFromPhysics(PhysicsEngine& physicsEngine) override;

	// Inherited via BasePlayer
	void RemoveFromRendererAndPhysics(Renderer& renderer, PhysicsEngine& physicsEngine) override;
};

