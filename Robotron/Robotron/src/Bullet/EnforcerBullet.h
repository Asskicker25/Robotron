#pragma once

#include "BaseBullet.h"

#include "../AnimationHelper/AnimationHelper.h"

class EnforcerBullet : public BaseBullet, public AnimationHelper
{
private :

	float rotateSpeed = 150.0f;
	// Inherited via BaseBullet
	void Start() override;
	void Update(float deltaTime) override;
	void SetPositionAndDir(glm::vec3 pos, glm::vec3 dir) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

public:
	EnforcerBullet();
	void CreateBulletInstance(Model* bullet) override;

	void CreateBulletInstance(Model* transform, const std::vector<Model*>& animationModels,
		Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine);

};

