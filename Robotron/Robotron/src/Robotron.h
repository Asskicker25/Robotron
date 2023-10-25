#pragma once
#include <Graphics/ApplicationWindow.h>
#include <Physics/PhysicsEngine.h>
#include "EntityManager/EntityManager.h"

class Robotron : public ApplicationWindow
{

private:

public:
	EntityManager entityManager;
	PhysicsEngine physicsEngine;

	void SetUp() override;
	void PreRender() override;
	void PostRender() override;
	void ProcessInput(GLFWwindow* window) override;
	void KeyCallBack(GLFWwindow* window, int& key, int& scancode, int& action, int& mods) override;
	void MouseButtonCallback(GLFWwindow* window, int& button, int& action, int& mods) override;

};

