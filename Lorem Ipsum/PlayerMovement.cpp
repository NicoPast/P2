#include "PlayerMovement.h"
#include "Animator.h"
#include "StoryManager.h"
#include "Entity.h"
#include "PlayerKBCtrl.h"

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
	if (deltaTime > 5)deltaTime = 5;
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
	if(!sm_->getCurrentScene()->ghWorld)
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
	//Buscamos el indice en el eje X para el tramo en el que se encuentra el jugador de la linea
	while (index < moveLine.size() - 1 && moveLine[index].getX() < tr_->getPos().getX())
		index++;
	index--;
	if (index < 0)
		index = 0;
	double finalX = moveLine[index+1].getX();
	double finalY = moveLine[index+1].getY();
	double firstX = moveLine[index].getX();
	double firstY = moveLine[index].getY();
	double actualY = tr_->getPos().getY();
	double actualX = pos.getX();
	
	double m = (finalY - firstY) / (finalX - firstX);//pendiente
	pos.setY(m*(actualX-firstX) + firstY);
	if (actualX > moveLine.back().getX())
	{
		pos.setX(moveLine.back().getX());
		GETCMP1_(PlayerKBCtrl)->resetTarget();
	}
	if (actualX < moveLine[0].getX())
	{
		pos.setX(moveLine[0].getX());
		GETCMP1_(PlayerKBCtrl)->resetTarget();

	}

}
void PlayerMovement::draw()
{
	//auto scene = sm_->getCurrentScene();
	//auto moveLine = scene->movementLine_;
	//int index = 0;
	//if (moveLine.back().getX() == 0 && moveLine.back().getY() == 0) //Caso default, no modificar la dirección, todavía la escena no tiene una linea de movimiento para el jugador
	//	return;
	////Buscamos el indice en el eje X para el tramo en el que se encuentra el jugador de la linea
	//while (index < moveLine.size() - 1 && moveLine[index].getX() < tr_->getPos().getX())
	//	index++;
	//index--;
	//if (index < 0)
	//	index = 0;
	//double finalX = moveLine[index + 1].getX();
	//double finalY = moveLine[index + 1].getY();
	//double firstX = moveLine[index].getX();
	//double firstY = moveLine[index].getY();
	//double actualY = tr_->getPos().getY();
	//double actualX = tr_->getPos().getX();
	//SDL_SetRenderDrawColor(game_->getRenderer(),255,0,255,255);
	//SDL_RenderDrawLine(game_->getRenderer(), firstX, firstY, finalX, finalY);
	//SDL_Point p = { tr_->getPos().getX(), ((((finalY - firstY) / (finalX / firstX)) * (actualX - firstX)) + firstY) };
	//SDL_RenderDrawPoint(game_->getRenderer(), p.x, p.y);
}