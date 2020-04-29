#include "PlayerKBCtrl.h"
#include "InputHandler.h"
#include "Entity.h"
#include "Transform.h"
#include "Tween.h"
#include <math.h>
#include "Sprite.h"

PlayerKBCtrl::PlayerKBCtrl() :
	PlayerKBCtrl(SDLK_RIGHT, SDLK_LEFT, SDLK_w, SDLK_s, nullptr, SDLK_LSHIFT, SDLK_RSHIFT) {
}

PlayerKBCtrl::PlayerKBCtrl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode phoneUp, SDL_Keycode phoneDown, Phone* phone, SDL_Keycode rightShift, SDL_Keycode leftShift) :
	Component(ecs::PlayerKBCtrl), //
	right_(right), //
	left_(left), //
	phoneUp_(phoneUp),
	phoneDown_(phoneDown),
	rightShift_(rightShift),
	leftShift_(leftShift),
	tr_(nullptr),
	phone_(phone)//
{
}

PlayerKBCtrl::~PlayerKBCtrl() {
}

void PlayerKBCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void PlayerKBCtrl::update() {

	InputHandler* ih = InputHandler::instance();

	if ((ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)))
	{
		target = ih->getMousePos().getX();
	}
	if ((ih->isKeyDown(rightShift_) || ih->isKeyDown(leftShift_) || 
		(ih->getMouseButtonState(InputHandler::RIGHT))))
		currentSpeed = runningSpeed;
	else currentSpeed = walkingSpeed;

	if (ih->isKeyDown(right_) || ih->isKeyDown(left_))
	{
		tr_->setVelX(0);

		if (ih->isKeyDown(right_))
		{
			tr_->setVelX(tr_->getVel().getX() +currentSpeed);
			target = NULL;
		}

		if (ih->isKeyDown(left_)) {
			tr_->setVelX(tr_->getVel().getX()-currentSpeed);
			target = NULL;
		}
	}
	else if (target == NULL && (ih->isKeyUp(left_) || ih->isKeyUp(right_)))
	{
		tr_->setVelX(0);
	}
	else if(target)
	{
		 double distance = target - tr_->getPos().getX();

		 if (abs(distance) <= currentSpeed)
		 {
			tr_->setPosX(target);
			target = NULL;
		 }

		 else tr_->setVelX(-currentSpeed * (signbit(distance) * 2 - 1));
	}

	if (ih->keyDownEvent() || ih->getMouseWheelMotion()!=0)
	{
		if (ih->isKeyDown(SDLK_s) || ih->getMouseWheelMotion() < 0) {
			phone_->getEntity()->getComponent<Tween>(ecs::Tween)->GoToA();
			phone_->getEntity()->getComponent<Sprite>(ecs::Sprite)->setTexture(game_->getTextureMngr()->getTexture(Resources::PhoneOff));
			phone_->hideIcons();
		}
		else if (ih->isKeyDown(SDLK_w) || ih->getMouseWheelMotion() > 0) {
			phone_->getEntity()->getComponent<Tween>(ecs::Tween)->GoToB();
		}
	} 

	//cout << "Target: "<<target << " Speed: " << currentSpeed << " Pos: " << tr_->getPos().getX() << "\n";
}