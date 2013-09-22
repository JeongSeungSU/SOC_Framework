#pragma once

#include "TransformParameters.h"
#include "LightParameters.h"
#include <vector>

namespace Rendering
{
	class Object;
	class Transform;
}

class Component
{
public:
	enum Type{
		Mesh,
		Camera,
		Light,
		User
	};

protected:
	Rendering::Object		*owner;
	Rendering::Transform	*ownerTransform;

public:
	Component();
	virtual ~Component(void);

public:
	virtual void Initialize() = 0;
	virtual void Update(float deltaTime);
	virtual void Render(Rendering::TransformParameters *transform, Rendering::Light::LightParameters *light);
	virtual void Destroy() = 0;

public:
	void SetOwner(Rendering::Object *object);
	Rendering::Object* GetOwner();
};