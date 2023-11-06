#pragma once
#include "../EntityManager/EntityManager.h"
#include "BasePlayer.h"
#include "../AnimationHelper/AnimationHelper.h"

class Player : public BasePlayer, public AnimationHelper
{
private:

	enum PlayerAnimationState;
	class Pimpl;
	Pimpl* pimpl;



public:
	Player();

	//Model* bulletPrefab;
	//Builder function
	void SetMaxHealth(const float& maxHealth) override;
	void SetSpeed(const float& speed) override;

	// Inherited via BasePlayer
	void UpdateVelocity(glm::vec3 velocity) override;
	void Shoot() override;

	// Inherited via BasePlayer
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

};

