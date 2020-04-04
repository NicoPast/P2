#include "Interactable.h"
#include "Entity.h"


Interactable::Interactable(string name, bool active) :
	Component(ecs::Interactable), //
	tr_(nullptr),
	colliding_ (false),
	name_(name),
	active_(active),
	f_(nullptr)
{
}

Interactable::~Interactable() {
}

void Interactable::init() {
	tr_ = GETCMP1_(Transform);
	text_ = GETCMP1_(Text);
}

void Interactable::update() {
	if (colliding_) {
		//if (text_ != nullptr) text_->setText(name_);
		if (InputHandler::instance()->isKeyDown(SDLK_e))
		{
			if(f_ !=nullptr)callback();
		}
	}
	//else if (text_ != nullptr) text_->resetText();
}

