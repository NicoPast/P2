#pragma once
#include "Component.h"
#include "Transform.h"

class SimpleMoveBehavior : public Component
{
public:
	SimpleMoveBehavior() :Component(ecs::SimpleMoveBehavior)
	{};
	~SimpleMoveBehavior() {};
	void  virtual init() override;
	void  virtual update() override;
	void moveTo(Vector2D pos, int speed);
private:
	Transform* tr_;
};