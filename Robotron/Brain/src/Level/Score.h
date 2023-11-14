#pragma once

#include "../EntityManager/Entity.h"

class Score : public Entity
{

private:

	std::vector<Model*> scoreModels;

	float posX = -12.0f;
	float posY = 8.0f;
	float digitSpacing = 0.6f;
	float fontSize = 0.01f;

	int currentScore = 0;

	Renderer* renderer;
	Shader* shader;

	// Inherited via Entity
	void Start() override;
	void Update(float deltaTime) override;
	void AddToRendererAndPhysics(Renderer* renderer, Shader* shader, PhysicsEngine* physicsEngine) override;
	void RemoveFromRendererAndPhysics(Renderer* renderer, PhysicsEngine* physicsEngine) override;

	void PrintNumber(int number);

public:

	Score();

	Model* zero;
	Model* one;
	Model* two;
	Model* three;
	Model* four;
	Model* five;
	Model* six;
	Model* seven;
	Model* eight;
	Model* nine;

	void AddScore(int score);

};

