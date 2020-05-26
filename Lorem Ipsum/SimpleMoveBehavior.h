#pragma once
#include "Component.h"
#include "Transform.h"
#include <functional>

class SimpleMoveBehavior : public Component
{
public:
	SimpleMoveBehavior() :Component(ecs::SimpleMoveBehavior)
	{};
	~SimpleMoveBehavior() {};
	void setFunc(std::function<void()> func) { f_ = func; };
	void  virtual init() override;
	void  virtual update() override;
	void moveTo(Vector2D pos, int speed);
private:
	Transform* tr_;
	std::function<void()> f_;
	Vector2D target = Vector2D(0,-1);
};