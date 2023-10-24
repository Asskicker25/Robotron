#pragma once
#include "../EntityManager/EntityManager.h"

class Player : public Entity
{
public:

	void Start() override;
	void Update() override;
	void AddToRenderer(Renderer& renderer) override;
};

