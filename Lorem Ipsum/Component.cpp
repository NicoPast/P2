#include "Component.h"

Component::Component(ecs::CmpId id) :
		entity_(nullptr), //
		game_(nullptr), //
		id_(id),
		enabled_(true)//
{
}

Component::~Component() {
}
