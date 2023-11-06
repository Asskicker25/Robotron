#include "Grunt.h"

Grunt::Grunt()
{
	InitializeEntity(this);
}

void Grunt::Start()
{
}

void Grunt::Update(float deltaTime)
{
	UpdateAnimation(deltaTime);
}

void Grunt::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	model->LoadModel("Assets/Models/Enemies/Grunt/grunt1.ply");
	model->transform.SetScale(glm::vec3(0.01f));
	model->isActive = false;
	phyObj->Initialize(model, AABB, STATIC, TRIGGER);

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.01f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(0, "Assets/Models/Enemies/Grunt/grunt1.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Grunt/grunt2.ply");
	AddModelToAnimationList(0, "Assets/Models/Enemies/Grunt/grunt3.ply");

	SetAnimationState(0);
}

void Grunt::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}

void Grunt::MoveTowardsPlayerPosition(float xPos, float yPos)
{
	Debugger::Print("PosX", xPos);
	Debugger::Print("PosY", yPos);
}
