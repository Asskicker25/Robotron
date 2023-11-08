#pragma once

#include <vector>
#include <Graphics/Model.h>
#include <Graphics/Renderer.h>

class AnimationHelper
{

private:

	Renderer* renderer = nullptr;
	Shader* shader = nullptr;

	int currentState = 0;
	int currentAnimation = 0;

	float animationStepTime = 0;
	float animationInterval = 0.5f;

	float modelScale = 0.01f;

	Model* currentModel = nullptr;
	Model* transformHolder = nullptr;

	void NextModel();
	Model* LoadModel(const std::string& path);

public:

	AnimationHelper();

	std::vector<std::vector<Model*>> animationModels;

	void AddModelToAnimationList(const int& stateIndex, const std::string& modelPath);
	void AddModelToAnimationList(const int& stateIndex, Model* model);
	void SetAnimationInterval(const float& animationInterval = 0);
	void UpdateAnimation(const float& deltaTime);

	void SetAnimationState(const int& currentState);
	void SetModelScale(const float& modelScale);
	void AssignRendererAndShader(Renderer* renderer, Shader* shader);
	void SetTransformHolder(Model* model);

	void DestroyAnimationModels();

};

