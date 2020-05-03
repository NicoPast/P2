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

void Interactable::update() {
	if (colliding_) {
		//if (text_ != nullptr) text_->setText(name_);
		if (InputHandler::instance()->keyDownEvent() && InputHandler::instance()->isKeyDown(SDLK_e))
		{
			if (f_ != nullptr)
			{
				callback();
				colliding_=false;
				cout << "calling callback\n";
			}
		}
	}
	//else if (text_ != nullptr) text_->resetText();
}

