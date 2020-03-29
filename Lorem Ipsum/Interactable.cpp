#include "Interactable.h"
#include "Entity.h"


Interactable::Interactable() :
	Component(ecs::Interactable), //
	tr_(nullptr),
	colliding_ (false){
}

Interactable::~Interactable() {
}

void Interactable::init() {
	tr_ = GETCMP1_(Transform);
}

void Interactable::update() {
	if (colliding_) {
		cout << "Colliding\n";
	}
}

