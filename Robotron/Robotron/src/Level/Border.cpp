#include "Border.h"

Border::Border()
{
	InitializeEntity(this);
	tag = "Border";
}

void Border::Start()
{
}

void Border::Update(float deltaTime)
{
}

void Border::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	Model* borderCube = new Model("Assets/Models/DefaultCube.fbx");
	borderCube->meshes[0]->material->SetBaseColor(glm::vec3(1.0f, 1.0f, 0.0f));

	Model* leftBorder = new Model();
	leftBorder->CopyFromModel(*borderCube);
	leftBorder->transform.SetScale(glm::vec3(0.15f, 7.25f,0.15f));
	leftBorder->transform.SetPosition(glm::vec3(
		-14.425f,
		0.0f,
		0.0f
	));

	Model* rightBorder = new Model();
	rightBorder->CopyFromModel(*borderCube);
	rightBorder->transform.SetScale(glm::vec3(0.15f, 7.25f, 0.15f));
	rightBorder->transform.SetPosition(glm::vec3(
		14.425f,
		0.0f,
		0.0f
	));
	
	Model* topBorder = new Model();
	topBorder->CopyFromModel(*borderCube);
	topBorder->transform.SetScale(glm::vec3(14.425f, 0.15f, 0.15f));
	topBorder->transform.SetPosition(glm::vec3(
		0.0f,
		7.1f,
		0.0f
	));

	Model* bottomBorder = new Model();
	bottomBorder->CopyFromModel(*borderCube);
	bottomBorder->transform.SetScale(glm::vec3(14.425f, 0.15f, 0.15f));
	bottomBorder->transform.SetPosition(glm::vec3(
		0.0f,
		-7.1f,
		0.0f
	));

	renderer->AddModel(leftBorder, shader);
	renderer->AddModel(rightBorder, shader);
	renderer->AddModel(topBorder, shader);
	renderer->AddModel(bottomBorder, shader);


	PhysicsObject* leftPhyObj = new PhysicsObject;
	leftPhyObj->Initialize(leftBorder, AABB, STATIC, TRIGGER);
	leftPhyObj->userData = this;

	PhysicsObject* rightPhyObj = new PhysicsObject;
	rightPhyObj->Initialize(rightBorder, AABB, STATIC, TRIGGER);
	rightPhyObj->userData = this;

	PhysicsObject* topPhyObj = new PhysicsObject;
	topPhyObj->Initialize(topBorder, AABB, STATIC, TRIGGER);
	topPhyObj->userData = this;

	PhysicsObject* bottomPhyObj = new PhysicsObject;
	bottomPhyObj->Initialize(bottomBorder, AABB, STATIC, TRIGGER);
	bottomPhyObj->userData = this;



	physicsEngine->AddPhysicsObject(leftPhyObj);
	physicsEngine->AddPhysicsObject(rightPhyObj);
	physicsEngine->AddPhysicsObject(topPhyObj);
	physicsEngine->AddPhysicsObject(bottomPhyObj);
}

void Border::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
}
