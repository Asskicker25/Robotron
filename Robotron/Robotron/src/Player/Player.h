#pragma once
#include "../EntityManager/EntityManager.h"
#include "iPlayer.h"

class Player : public iPlayer
{
private:
	float maxHealth;
	float speed;

public:

	void SetMaxHealth(const float& maxHealth);
	void SetSpeed(const float& speed);

	// Inherited via iPlayer
	void Shoot() override;
	void Start() override;
	void Update() override;
	void AddToRenderer(Renderer& renderer) override;

};

