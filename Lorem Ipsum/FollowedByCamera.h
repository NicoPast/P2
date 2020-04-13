#pragma once
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

class FollowedByCamera : public Component
{

public:
	FollowedByCamera(Camera* cam, Transform* tr) : Component(ecs::FollowedByCamera), cam_(cam), tr_(tr) {};

	void init();
	void update();

private:

	Transform* tr_;
	Camera* cam_;

};