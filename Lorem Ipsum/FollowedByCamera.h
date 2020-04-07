#pragma once
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

class FollowedByCamera : public Component
{

public:
	FollowedByCamera(Camera* cam) : Component(ecs::FollowedByCamera), cam_(cam), tr_(nullptr) {};

	void init();
	void update();

private:

	Transform* tr_;
	Camera* cam_;

};