#include "Transform.h"
#include "Entity.h"
Transform::Transform() :
		Component(ecs::Transform), position_(), //
		velocity_(), //
		width_(), //
		height_(), //
		rotation_() //
{
}

Transform::Transform(Vector2D pos, Vector2D vel, double width,
		double height, double rotation, Transform* parent) :
		Component(ecs::Transform), position_(pos), //
		velocity_(vel), //
		width_(width), //
		height_(height), //
		rotation_(0.0), //
		parent_(parent) //
{
}

Transform::Transform(double x, double y, double width, double height, Transform* parent) :
	Component(ecs::Transform),
	position_({ x, y }),
	velocity_({ 0.0, 0.0 }),
	width_(width),
	height_(height),
	rotation_(0.0),
	parent_(parent)
{
}

Transform::~Transform() {
}

void Transform::setActiveChildren(bool b) {
	for (auto tr : children_) {
		tr->getEntity()->setActive(b);
	}
}
