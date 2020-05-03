#include "Interactable.h"
#include "StoryManager.h"
#include "Entity.h"


Interactable::Interactable() :
	Component(ecs::Interactable), //
	tr_(nullptr),
	colliding_ (false)
{
}

Interactable::~Interactable() {
}

void Interactable::init() {
	tr_ = GETCMP1_(Transform);
	text_ = GETCMP1_(Text);
}

