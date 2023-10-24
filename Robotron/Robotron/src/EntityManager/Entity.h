#pragma once

#include <Graphics/Renderer.h>

class Entity
{
public:
	virtual ~Entity() {};

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void AddToRenderer(Renderer& renderer) = 0;
};

