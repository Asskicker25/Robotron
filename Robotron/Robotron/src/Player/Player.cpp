#include "Player.h"
#include <Graphics/Debugger.h>
#include "../InputManager/InputManager.h"
#include "Bullet/BulletFactory.h"

#pragma region Pimpl

class Player::Pimpl
{
	glm::vec3 faceDir;
	float shootRadiusOffset;
	float shootYOffset;
	Player* player;

public:

	Renderer* renderer;
	Shader* shader;
	BulletFactory* bulletFactory;
	PhysicsEngine* physicsEngine;

	Pimpl(Player* player);
	const glm::vec3& CalculateDirection(const glm::vec3 velocity);

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
	if (glm::length(velocity) == 0)
	{
		return faceDir;
	}
	
	faceDir = glm::normalize(velocity);

	return faceDir;
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

	//Model* newBullet = new Model();

	////newBullet->CopyFromModel(*bulletPrefab);
	//

	//PhysicsObject* bulletPhyObj = new PhysicsObject();
	//bulletPhyObj->Initialize(newBullet, SPHERE, DYNAMIC);
}

void Player::Start()
{
	//bulletPrefab->LoadModel("Assets/Models/DefaultSphere.fbx");
}

void Player::Update(float deltaTime)
{
}

void Player::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	pimpl->renderer = renderer;
	pimpl->shader = shader;

	model->LoadModel("Assets/Models/Player/player1.ply");
	model->transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	model->transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
	model->transform.SetScale(glm::vec3(0.01f));

	renderer->AddModel(model, shader);

	phyObj->Initialize(model, AABB, DYNAMIC, SOLID);

	phyObj->userData = this;

	physicsEngine->AddPhysicsObject(phyObj);

	pimpl->bulletFactory->AssignRenderesAndPhysics(renderer, shader, physicsEngine);
}

void Player::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	model->isActive = false;
	physicsEngine->RemovePhysicsObject(phyObj);
}


