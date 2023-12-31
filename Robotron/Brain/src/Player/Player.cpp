#include "Player.h"
#include <Graphics/Debugger.h>
#include "../InputManager/InputManager.h"
#include "../Bullet/BulletFactory.h"
#include "../AI/Humans/Human.h"

enum Player::PlayerAnimationState
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3
};

#pragma region Pimpl

class Player::Pimpl
{
	glm::vec3 faceDir;
	float shootRadiusOffset;
	float shootYOffset;
	Player* player;

	float timeStep = 2.0;
	float posUpdateInterval = 0.5f;

public:

	Renderer* renderer;
	Shader* shader;
	BulletFactory* bulletFactory;
	PhysicsEngine* physicsEngine;

	PlayerAnimationState playerState = PlayerAnimationState::NONE;

	glm::vec3 currentVelocity = glm::vec3(0.0f);

	Pimpl(Player* player);

	const glm::vec3& CalculateDirection(const glm::vec3 velocity);
	void CalculateAnimationState(const float& deltaTime);
	void ChangeAnimationState(PlayerAnimationState animationState);
	void UpdatePlayerPosition(float deltaTime);

	void OnCollision(PhysicsObject* otherObject);

	const glm::vec3& GetFirePosition();
	const glm::vec3& GetFireDirection();
};

Player::Pimpl::Pimpl(Player* player)
{
	bulletFactory = new BulletFactory();
	this->player = player;

	faceDir = glm::vec3(1.0f, 0.0f, 0.0f);
	shootRadiusOffset = 0.5f;
	shootYOffset = 0.75f;
}

const glm::vec3& Player::Pimpl::CalculateDirection(const glm::vec3 velocity)
{
	currentVelocity = velocity;

	if (glm::length(velocity) == 0)
	{
		return faceDir;
	}
	
	faceDir = glm::normalize(velocity);

	return faceDir;
}

void Player::Pimpl::CalculateAnimationState(const float& deltaTime)
{

	if (glm::length(currentVelocity) == 0)
	{
		return;
	}

	if (currentVelocity.x > 0)
	{
		ChangeAnimationState(RIGHT);
	}
	else if (currentVelocity.x < 0)
	{
		ChangeAnimationState(LEFT);
	}
	else if (currentVelocity.y > 0)
	{
		ChangeAnimationState(UP);
	}
	else if (currentVelocity.y < 0)
	{
		ChangeAnimationState(DOWN);
	}

	player->UpdateAnimation(deltaTime);

}

void Player::Pimpl::ChangeAnimationState(PlayerAnimationState animationState)
{
	if (playerState == animationState) return;

	playerState = animationState;

	player->SetAnimationState(playerState);
}

void Player::Pimpl::UpdatePlayerPosition(float deltaTime)
{
	timeStep += deltaTime;
	
	if (timeStep > posUpdateInterval)
	{
		timeStep = 0;

		player->gameMediator->UpdatePlayerPosition(player->model->transform.position.x, player->model->transform.position.y);
	}
}

void Player::Pimpl::OnCollision(PhysicsObject* otherObject)
{
	Entity* other = (Entity*)otherObject->userData;
	std::string tag = other->tag;



	if (tag == "Enemy" || tag == "Hulk")
	{
		player->Destroy();
		player->gameMediator->OnPlayerDead();
	}

	if (tag == "EnforcerBullet" || tag == "TrackingMissile" || tag == "BouncingOrb")
	{
		other->Destroy();
		player->Destroy();
		player->gameMediator->OnPlayerDead();
	}

	if (tag == "Human")
	{
		player->gameMediator->AddScore(1000);
		((Human*)other)->RemoveFromHumanManager();

	}
}

const glm::vec3& Player::Pimpl::GetFirePosition()
{
	return glm::vec3(player->model->transform.position.x,
		player->model->transform.position.y + shootYOffset,
		player->model->transform.position.z)
		+ (faceDir * shootRadiusOffset);
}

const glm::vec3& Player::Pimpl::GetFireDirection()
{
	return faceDir;
}

#pragma endregion


Player::Player() : pimpl { new Pimpl(this) }
{
	model = new Model();
	phyObj = new PhysicsObject();

	tag = "Player";
	entityId = "Player";
	InitializeEntity(this);
}

void Player::SetMaxHealth(const float& maxHealth)
{
	this->maxHealth = maxHealth;
}

void Player::SetSpeed(const float& speed)
{
	this->speed = speed;
}

void Player::UpdateVelocity(glm::vec3 velocity)
{
	phyObj->velocity = velocity;
	pimpl->CalculateDirection(velocity);
}

void Player::Shoot()
{
	BaseBullet* bullet = pimpl->bulletFactory->CreateBaseBullet();

	bullet->SetPositionAndDir(pimpl->GetFirePosition(), pimpl->GetFireDirection());
}

void Player::Start()
{
	//bulletPrefab->LoadModel("Assets/Models/DefaultSphere.fbx");
}

void Player::Update(float deltaTime)
{
	pimpl->CalculateAnimationState(deltaTime);
	pimpl->UpdatePlayerPosition(deltaTime);
}

void Player::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	pimpl->renderer = renderer;
	pimpl->shader = shader;

	//TransformHolder
	model->LoadModel("Assets/Models/Player/player4.ply");
	model->transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	model->transform.SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	model->transform.SetScale(glm::vec3(0.0075f));
	model->isActive = false;

	renderer->AddModel(model, shader);
	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER,true);
	phyObj->userData = this;
	physicsEngine->AddPhysicsObject(phyObj);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			pimpl->OnCollision(otherObject);
		});

	pimpl->bulletFactory->AssignRenderesAndPhysics(renderer, shader, physicsEngine);

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	//Left
	AddModelToAnimationList(LEFT, "Assets/Models/Player/player1.ply");
	AddModelToAnimationList(LEFT, "Assets/Models/Player/player2.ply");
	AddModelToAnimationList(LEFT, "Assets/Models/Player/player3.ply");
	

	//Right
	AddModelToAnimationList(RIGHT, "Assets/Models/Player/player4.ply");
	AddModelToAnimationList(RIGHT, "Assets/Models/Player/player5.ply");
	AddModelToAnimationList(RIGHT, "Assets/Models/Player/player6.ply");

	//Up
	AddModelToAnimationList(UP, "Assets/Models/Player/player10.ply");
	AddModelToAnimationList(UP, "Assets/Models/Player/player11.ply");
	AddModelToAnimationList(UP, "Assets/Models/Player/player12.ply");

	//Down
	AddModelToAnimationList(DOWN, "Assets/Models/Player/player7.ply");
	AddModelToAnimationList(DOWN, "Assets/Models/Player/player8.ply");
	AddModelToAnimationList(DOWN, "Assets/Models/Player/player9.ply");

	SetAnimationState(RIGHT);
}

void Player::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	DestroyAnimationModels();

	renderer->RemoveModel(model);
	//model->isActive = false;
	physicsEngine->RemovePhysicsObject(phyObj);
}


