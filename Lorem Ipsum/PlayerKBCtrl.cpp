#include "PlayerKBCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"
#include <math.h>

PlayerKBCtrl::PlayerKBCtrl() :
	PlayerKBCtrl(SDLK_RIGHT, SDLK_LEFT, SDLK_LSHIFT, SDLK_RSHIFT) {
}

PlayerKBCtrl::PlayerKBCtrl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode rightShift, SDL_Keycode leftShift) :
	Component(ecs::PlayerKBCtrl), //
	right_(right), //
	left_(left), //
	rightShift_(rightShift),
	leftShift_(leftShift),
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

	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT))
	{
		target = ih->getMousePos().getX();
	}

	if (ih->isKeyDown(rightShift_) || ih->isKeyDown(leftShift_)) currentSpeed = runningSpeed;

	else currentSpeed = walkingSpeed;

	if (ih->isKeyDown(right_) && tr_->getPos().getX() + tr_->getW() < rightBound_) {
		tr_->setVelX(+currentSpeed);
		target = NULL;
	}

	else if (ih->isKeyDown(left_) && tr_->getPos().getX() > leftBound_) {
		tr_->setVelX(-currentSpeed);
		target = NULL;
	}

	else if (target != NULL) 
	{
		 double distance = target - tr_->getPos().getX();

		 if (abs(distance) <= currentSpeed)
		 {
			tr_->setPosX(target);
			target = NULL;
		 }

		 else tr_->setVelX(-currentSpeed * (signbit(distance) * 2 - 1));
	}

	else
	{
		tr_->setVelX(0);
	}

	//cout << "Target: "<<target << " Speed: " << currentSpeed << " Pos: " << tr_->getPos().getX() << "\n";
}