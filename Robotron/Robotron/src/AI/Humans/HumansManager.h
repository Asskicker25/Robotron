#pragma once

#include "../../EntityManager/Entity.h"
#include "Human.h"

class HumansManager : public Entity
{

public:
	HumansManager();

private:

	static const int humanMinCount = 3;
	static const int humanMaxCount = 6;

	static constexpr float spawnXRange = 12.5f;
	static constexpr float spawnYRange = 5.5f;

	static constexpr float centerRadius = 2.0f;

	int humanCount = 0;

	std::vector<Human*> listOfHumans;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	void SpawnHumans();

};

