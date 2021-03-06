#pragma once
#include "Entity.h"
#include "Component.h"
#include "Camera.h"

class CameraController: public Component
{
public:
	CameraController(Camera* cam) : Component(ecs::CameraController), cam_(cam), oldPos_() {};
	~CameraController() {};

	void update();

protected:
	Vector2D oldPos_ = Vector2D(0, 0);
	Camera* cam_ = nullptr;

	bool dragging_ = false;
};