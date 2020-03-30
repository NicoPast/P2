#include "Interactable.h"
#include "Entity.h"


Interactable::Interactable(string name, bool active) :
	Component(ecs::Interactable), //
	tr_(nullptr),
	colliding_ (false),
	name_(name),
	active_(active){
}

Interactable::~Interactable() {
}

void Interactable::init() {
	tr_ = GETCMP1_(Transform);
	text_ = GETCMP1_(Text);
}

void Interactable::update() {
	if (colliding_) {
		if (text_ != nullptr) text_->setText(name_);
	}

	else if (text_ != nullptr) text_->setText("");
}

