#include "PlayerMovement.h"
#include "Animator.h"
#include "StoryManager.h"
#include "Entity.h"

PlayerMovement::PlayerMovement(StoryManager* sm) :
	Component(ecs::PlayerMovement), tr_(nullptr), sm_(sm) {
}

PlayerMovement::~PlayerMovement() {
}

void PlayerMovement::init() {
	tr_ = GETCMP1_(Transform);
}

void PlayerMovement::update() {

	Uint32 deltaTime = (game_->getTime() - frameTime) / 10;
	frameTime = game_->getTime();
	if (deltaTime > 20)deltaTime = 20;
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
	perspective(v);
	tr_->setPos(v);

	//animaciones del jugador: idle y movimiento lateral
	Animator<Transform*>* animator = entity_->getComponent<Animator<Transform*>>(ecs::Animator);

	animator->changeAnim((tr_->getVel().getX() == 0) ? Resources::IdleSDLAnim : Resources::WalkingSDLAnim);
	if (tr_->getVel().getX() != 0)flip = tr_->getVel().getX() > 0;
	animator->flipHor(flip);

}
void PlayerMovement::perspective(Vector2D& pos)
{
	auto scene = sm_->getCurrentScene();
	auto moveLine = scene->movementLine_;
	if (moveLine.back().getX() == 0 && moveLine.back().getY() == 0) //Caso default, no modificar la dirección, todavía la escena no tiene una linea de movimiento para el jugador
		return;
	int index = 0;
	Vector2D vel = {0,0};
	//Buscamos el indice en el eje X para el tramo en el que se encuentra el jugador de la linea
	while (index < moveLine.size() - 1 && !(moveLine[index].getX() < tr_->getPos().getX() && moveLine[index + 1].getX() > tr_->getPos().getX()))
		index++;


	//Límite izquierdo
	if (index == 0)
	{
		double finalX = moveLine[1].getX();
		double finalY = moveLine[1].getY();
		double firstX = moveLine[0].getX();
		double firstY = moveLine[0].getY();
		double actualY = tr_->getPos().getY();
		double actualX = tr_->getPos().getX();

		double scale =  (firstX + finalX)/ actualX;
		pos.setY(firstY + (finalY-firstY)*scale);
	}
	//Límite derecho
	else  if (index == moveLine.size() - 1)
	{
		double finalX = moveLine[index].getX();
		double finalY = moveLine[index].getY();
		double firstX = moveLine[index-1].getX();
		double firstY = moveLine[index-1].getY();
		double actualY = tr_->getPos().getY();
		double actualX = tr_->getPos().getX();

		double scale = (firstX + finalX) / actualX ;
		pos.setY(firstY + (finalY - firstY) * scale);
	}

}