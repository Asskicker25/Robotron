#pragma once

#include "../EntityManager/Entity.h"

class iPlayer : public Entity
{
public:
	virtual ~iPlayer() {};
	virtual void Shoot() = 0;

	// Inherited via Entity
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void AddToRenderer(Renderer& renderer) = 0;
};

