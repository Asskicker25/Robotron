#include "BaseAI.h"
#include "../Utilities/Random.h"

const glm::vec2 directions[] = {
		glm::vec2(0, 1),    // UP
		glm::vec2(1, 1),    // UPRIGHT
		glm::vec2(1, 0),    // RIGHT
		glm::vec2(1, -1),    // DOWNRIGHT
		glm::vec2(0, -1),   // DOWN
		glm::vec2(-1, -1),  // DOWNLEFT
		glm::vec2(-1, 0),   // LEFT
		glm::vec2(-1, 1),   // UPLEFT
};

BaseAI::BaseAI()
{
	model = new Model();
	phyObj = new PhysicsObject();

	phyObj->userData = this;

	dirChangeInterval = GetRandomFloatNumber(dirChangeIntervalMin, dirChangeIntervalMax);
	timeStep = dirChangeInterval;
}


glm::vec2 BaseAI::GetRandomDirection(bool reflectedRandom)
{
	int randomDirIndex = -1;

	if (reflectedRandom)
	{
		do
		{
			randomDirIndex = GetRandomIntNumber(0, 7);
		} while (randomDirIndex == currentDirection || randomDirIndex == currentDirection - 1 || randomDirIndex == currentDirection + 1);
	}
	else
	{
		do
		{
			randomDirIndex = GetRandomIntNumber(0, 7);
		} while (randomDirIndex == currentDirection);
	}


	currentDirection = randomDirIndex;

	return glm::normalize(directions[currentDirection]);
}

void BaseAI::UpdateRandomMoveDirection(float deltaTime)
{
	if (!isMovingRandom) return;

	timeStep += deltaTime;

	if (timeStep > dirChangeInterval)
	{
		ChangeRandomDirection(false);
	}
}

void BaseAI::Update(float deltaTime)
{
	UpdateAI(deltaTime);
	UpdateRandomMoveDirection(deltaTime);
}

void BaseAI::ChangeRandomDirection(bool reflectedRandom)
{
	if (reflectedRandom)
	{
		phyObj->velocity = -phyObj->GetCollisionNormals()[0] * speed;
	}
	else
	{
		dirChangeInterval = GetRandomFloatNumber(dirChangeIntervalMin, dirChangeIntervalMax);
		timeStep = 0;
		phyObj->velocity = glm::vec3(GetRandomDirection(), 0.0f) * speed;
	}
}

