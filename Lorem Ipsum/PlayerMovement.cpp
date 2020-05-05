#include "PlayerMovement.h"
#include "Animator.h"

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

	else if(x +tr_->getW() >= game_->getCamera()->getLimitX())
	{
		v.setX(game_->getCamera()->getLimitX() - tr_->getW());
		tr_->setVelX(0);
	}
	tr_->setPos(v);

	//animaciones del jugador: idle y movimiento lateral
	Animator<Transform*>* animator = entity_->getComponent<Animator<Transform*>>(ecs::Animator);

	//if (tr_->getVel().getX() == 0 /*&& animator->getAnim() != Resources::IdleSDLAnim*/)
	//{
	//	animator->changeAnim(Resources::IdleSDLAnim);
	//}
	//else if (tr_->getVel().getX() < 0 /*&& (animator->getAnim() != Resources::WalkingSDLAnim || flip)*/)
	//{
	//	animator->changeAnim(Resources::WalkingSDLAnim);
	//	flip = false;
	//}

	//else if (tr_->getVel().getX() > 0 /*&& (animator->getAnim() != Resources::WalkingSDLAnim || !flip)*/)
	//{
	//	animator->changeAnim(Resources::WalkingSDLAnim);
	//	flip = true;
	//}
	animator->changeAnim((tr_->getVel().getX() == 0) ? Resources::IdleSDLAnim : Resources::WalkingSDLAnim);
	if (tr_->getVel().getX() != 0)flip = tr_->getVel().getX() > 0;
	animator->flipHor(flip);

}