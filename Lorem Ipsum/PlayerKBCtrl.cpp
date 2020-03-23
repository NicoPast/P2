#include "PlayerKBCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"

PlayerKBCtrl::PlayerKBCtrl() :
	PlayerKBCtrl(SDLK_RIGHT, SDLK_LEFT, SDLK_SPACE) {
}

PlayerKBCtrl::PlayerKBCtrl(SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop) :
	Component(ecs::PlayerKBCtrl), //
	right_(up), //
	left_(down), //
	stop_(stop),
	tr_(nullptr)//
{
}

PlayerKBCtrl::~PlayerKBCtrl() {
}

void PlayerKBCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void PlayerKBCtrl::update() {

	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(right_)) {
			tr_->setVelX(+speed);
		}
		else if (ih->isKeyDown(left_)) {
			tr_->setVelX(-speed);
		}
		else if (ih->isKeyDown(stop_)) {
			tr_->setVelX(0);
		}
	}

	else tr_->setVelX(0);
}