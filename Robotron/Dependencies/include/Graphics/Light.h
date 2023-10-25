#pragma once

#include "Transform.h"
#include "Material.h"
#include "Model.h"

enum LightType
{
	Point = 0,
	Spot = 1,
	Directional = 2,
};
 
class Light 
{

private:
	Material material;

public:
	bool isActive = true;

	LightType lightType;

	Transform* transform;
	Model* lightModel;

	glm::vec4 attenuation;

	float intensity;
	float innerAngle;
	float outerAngle;

	Light(Model& model, LightType lightType = LightType::Point);
	Light(Model* model, LightType lightType = LightType::Point);
	Light();
	~Light();

	void InitializeLight(Model& model, LightType lightType = LightType::Point);
	void InitializeLight(Model* model, LightType lightType = LightType::Point);

	glm::vec3 GetLightColor();
	glm::vec3 GetAmbientColor();
	float GetAmbientValue();

	void SetLightColor(glm::vec3 color);
	void SetAmbientColor(glm::vec3 color);
	void SetAmbientValue(float ambientValue);
};

