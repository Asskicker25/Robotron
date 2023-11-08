#include "AnimationHelper.h"

AnimationHelper::AnimationHelper()
{
	animationModels.resize(4);
}

void AnimationHelper::AddModelToAnimationList(const int& stateIndex, const std::string& modelPath)
{
	animationModels[stateIndex].push_back(LoadModel(modelPath));
}

void AnimationHelper::AddModelToAnimationList(const int& stateIndex, Model* model)
{
	renderer->AddModel(model, shader);
	animationModels[stateIndex].push_back(model);
}

void AnimationHelper::SetAnimationInterval(const float& animationInterval)
{
	this->animationInterval = animationInterval;
}

void AnimationHelper::UpdateAnimation(const float& deltaTime)
{
	currentModel->transform.SetPosition(transformHolder->transform.position);

	animationStepTime += deltaTime;

	if (animationStepTime > animationInterval)
	{
		animationStepTime = 0;

		NextModel();
	}
}

void AnimationHelper::SetAnimationState(const int& currentState)
{
	if (currentModel != nullptr)
	{
		currentModel->isActive = false;
	}

	this->currentState = currentState;
	currentAnimation = 0;

	currentModel = animationModels[currentState][currentAnimation];
	currentModel->transform.SetPosition(transformHolder->transform.position);
	currentModel->isActive = true;
}




void AnimationHelper::NextModel()
{
	
	currentAnimation++;

	if (animationModels[currentState].size() <= currentAnimation)
	{
		currentAnimation = 0;
	}

	if (currentModel != nullptr)
	{
		currentModel->isActive = false;
	}


	currentModel = animationModels[currentState][currentAnimation];	
	currentModel->transform.SetPosition(transformHolder->transform.position);
	currentModel->isActive = true;
}

Model* AnimationHelper::LoadModel(const std::string& path)
{
	Model* model = new Model(path);

	model->transform.SetScale(glm::vec3(this->modelScale));
	model->isActive = false;

	renderer->AddModel(model, shader);

	return model;
}

void AnimationHelper::SetModelScale(const float& modelScale)
{
	this->modelScale = modelScale;
}

void AnimationHelper::AssignRendererAndShader(Renderer* renderer, Shader* shader)
{
	this->renderer = renderer;
	this->shader = shader;
}

void AnimationHelper::DestroyAnimationModels()
{
	for (std::vector<Model*> models : animationModels)
	{
		for (Model* model : models)
		{
			model->isActive = false;
			renderer->RemoveModel(model);
			
			delete model;
		}
	}
}

void AnimationHelper::SetTransformHolder(Model* model)
{
	transformHolder = model;
}
