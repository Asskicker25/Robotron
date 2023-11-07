#include "Human.h"
#include "HumansManager.h"
#include "../../Utilities/Random.h"

const std::string humanName[] = 
{
	"daddy", "mommy", "mikey"
};

Human::Human(HumanType humanType)
{
	this->humanType = humanType;
	isMovingRandom = true;

	speed = GetRandomFloatNumber(speedMin, speedMax);

	tag = "Human";
}

void Human::Start()
{
}

void Human::UpdateAI(float deltaTime)
{
	UpdateAnimationState();
	UpdateAnimation(deltaTime);
}

void Human::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{

	std::string path = "Assets/Models/Humans/" + humanName[humanType] + "/" + humanName[humanType];

	//TransformHolder
	model->LoadModel(path + "2.ply");
	model->transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	model->transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	model->transform.SetScale(glm::vec3(0.0075f));
	model->isActive = false;

	renderer->AddModel(model, shader);
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER, true);
	phyObj->userData = this;
	physicsEngine->AddPhysicsObject(phyObj);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* entity = (Entity*)otherObject->userData;
			std::string tag = entity->tag;
			
			if (tag == "Border")
			{
				ChangeRandomDirection();
			}
		});

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	//Left
	AddModelToAnimationList(LEFT, path + "1.ply");
	AddModelToAnimationList(LEFT, path + "2.ply");
	AddModelToAnimationList(LEFT, path + "3.ply");


	//Right
	AddModelToAnimationList(RIGHT, path + "4.ply");
	AddModelToAnimationList(RIGHT, path + "5.ply");
	AddModelToAnimationList(RIGHT, path + "6.ply");

	//Up
	AddModelToAnimationList(UP, path + "10.ply");
	AddModelToAnimationList(UP, path + "11.ply");
	AddModelToAnimationList(UP, path + "12.ply");

	//Down
	AddModelToAnimationList(DOWN, path + "7.ply");
	AddModelToAnimationList(DOWN, path + "8.ply");
	AddModelToAnimationList(DOWN, path + "9.ply");

	SetAnimationState(RIGHT);
}

void Human::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	physicsEngine->RemovePhysicsObject(phyObj);
}

void Human::MoveTowardsPlayerPosition(float xPos, float yPos)
{

}


void Human::OnPlayerDead()
{
}

void Human::ChangeAnimationState(HumanAnimationState animationState)
{
	if (currentAnimation == animationState) return;

	currentAnimation = animationState;

	SetAnimationState(animationState);
}

void Human::UpdateAnimationState()
{

	if (phyObj->velocity.x > 0)
	{
		ChangeAnimationState(RIGHT);
	}
	else if(phyObj->velocity.x < 0)
	{
		ChangeAnimationState(LEFT);
	}
	else if (phyObj->velocity.y > 0)
	{
		ChangeAnimationState(UP);
	}
	else if (phyObj->velocity.y < 0)
	{
		ChangeAnimationState(DOWN);
	}
}


