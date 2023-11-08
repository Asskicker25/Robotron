#include "EnforcerBullet.h"


EnforcerBullet::EnforcerBullet()
{
	tag = "EnforcerBullet";
	phyObj->userData = this;

	bulletSpeed = 10.0f;
}

void EnforcerBullet::Start()
{
}

void EnforcerBullet::Update(float deltaTime)
{
	//UpdateAnimation(deltaTime);

	model->transform.rotation.z += deltaTime * rotateSpeed;
}

void EnforcerBullet::SetPositionAndDir(glm::vec3 pos, glm::vec3 dir)
{
}

void EnforcerBullet::CreateBulletInstance(Model* bullet)
{
	model->CopyFromModel(*bullet);
	phyObj->Initialize(model, SPHERE, DYNAMIC, TRIGGER, true);

	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* other = (Entity*)otherObject->userData;
			std::string tag = other->tag;

			if (tag == "Border")
			{
				Destroy();
			}
		});
}

void EnforcerBullet::AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{

}

void EnforcerBullet::RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine)
{
	//DestroyAnimationModels();

	/*renderer->RemoveModel(localAnimationModels[0]);
	renderer->RemoveModel(localAnimationModels[1]);
	renderer->RemoveModel(localAnimationModels[2]);*/

	renderer->RemoveModel(model);

	physicsEngine->RemovePhysicsObject(phyObj);
}

void EnforcerBullet::CreateBulletInstance(Model* transform, const std::vector<Model*>& animationModels,
	Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine)
{
	/*model->CopyFromModel(*transform);
	model->isActive = false;

	Model* model1 = new Model();
	model1->CopyFromModel(*animationModels[0]);
	model1->isActive = false;

	Model* model2 = new Model();
	model2->CopyFromModel(*animationModels[1]);
	model2->isActive = false;

	Model* model3 = new Model();
	model3->CopyFromModel(*animationModels[2]);
	model3->isActive = false;

	AssignRendererAndShader(renderer, shader);
	SetTransformHolder(model);
	SetModelScale(0.0075f);
	SetAnimationInterval(0.1f);

	AddModelToAnimationList(0, model1);
	AddModelToAnimationList(0, model2);
	AddModelToAnimationList(0, model3);


	phyObj->Initialize(model, AABB, DYNAMIC, TRIGGER, true);
	phyObj->AssignCollisionCallback([this](PhysicsObject* otherObject)
		{
			Entity* other = (Entity*)otherObject->userData;
			std::string tag = other->tag;

			if (tag == "Border")
			{
				Destroy();
			}
		});*/
}

