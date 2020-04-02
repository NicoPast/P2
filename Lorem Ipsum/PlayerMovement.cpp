#include "PlayerMovement.h"

#include "Entity.h"

PlayerMovement::PlayerMovement() :
	Component(ecs::PlayerMovement), tr_(nullptr) {
}

PlayerMovement::~PlayerMovement() {
}

void PlayerMovement::init() {
	tr_ = GETCMP1_(Transform);
}

void PlayerMovement::update() {

	Uint32 deltaTime = (game_->getTime() - frameTime) / 10;
	frameTime = game_->getTime();
	Vector2D v = tr_->getPos() + tr_->getVel() * deltaTime;

	double x = v.getX();

	if (x <= 0) {
		v.setX(0);
		tr_->setVelX(0);
	}
	else if (x + tr_->getW() >= game_->getWindowWidth()) {
		v.setX(game_->getWindowWidth() - tr_->getW());
		tr_->setVelY(0);
	}

	tr_->setPos(v);
}