#pragma once
#include "../EntityManager/EntityManager.h"
#include "iPlayer.h"
#include "../InputManager/iInputListener.h"

class Player : public iPlayer, public iInputListener
{
private:
	float maxHealth;
	float speed;

	Model model;
	PhysicsObject phyObject;

public:

	void SetMaxHealth(const float& maxHealth);
	void SetSpeed(const float& speed);

	// Inherited via iPlayer
	void Shoot() override;
	void Start() override;
	void Update() override;
	void AddToRenderer(Renderer& renderer, Shader* shader) override;
	void AddToPhysics(PhysicsEngine& physicsEngine) override;


	Player() = default;

	// Inherited via iInputListener
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHeld(const int& key) override;
};

