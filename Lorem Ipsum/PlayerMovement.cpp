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
	if (moveLine.back().getX() == 0 && moveLine.back().getY() == 0) //Caso default, no modificar la direcci�n, todav�a la escena no tiene una linea de movimiento para el jugador
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
#ifdef _DEBUG
	added_ = false;
#endif // _DEBUG

}
void PlayerMovement::draw()
{
#ifdef _DEBUG
	if (StoryManager::instance()->showingHitbox_)
	{
		auto scene = sm_->getCurrentScene();
		auto moveLine = scene->movementLine_;
		if (moveLine.back().getX() == 0 && moveLine.back().getY() == 0) //Caso default, no modificar la direcci�n, todav�a la escena no tiene una linea de movimiento para el jugador
			return;
		int col = 255 / moveLine.size();;
		for (int index = 0; index < moveLine.size()-1; index++)
		{
			double finalX = moveLine[index + 1].getX();
			double finalY = moveLine[index + 1].getY();
			double firstX = moveLine[index].getX();
			double firstY = moveLine[index].getY();
			double actualY = tr_->getPos().getY();
			double actualX = tr_->getPos().getX();
			SDL_SetRenderDrawColor(game_->getRenderer(), (1+col)*index, 0, (1+col) * index, 255);
			SDL_RenderDrawLine(game_->getRenderer(), firstX, firstY, finalX, finalY);
			SDL_Point p = { tr_->getPos().getX(), ((((finalY - firstY) / (finalX / firstX)) * (actualX - firstX)) + firstY) };
			SDL_SetRenderDrawColor(game_->getRenderer(), 255, 255, 0, 255);
			SDL_RenderDrawPoint(game_->getRenderer(), firstX, firstY);
			SDL_RenderDrawPoint(game_->getRenderer(), finalX, finalY);
		}

	}
	lineEditing_ = StoryManager::instance()->showingHitbox_;
	if (lineEditing_)
	{
		auto scene = sm_->getCurrentScene();
		scene->movementLine_;
		auto ih = InputHandler::instance();
		if (ih->isKeyDown(SDLK_RETURN))
		{
			cout << "{";
			for (Vector2D v : scene->movementLine_)
				cout << "{"<< v.getX() << ","<<v.getY() << " " << "}" ;
			cout << "} \n";
		}
		if (!added_ && ih->keyDownEvent()&& ih->isKeyDown(SDLK_INSERT))
		{
			scene->movementLine_.push_back(Vector2D(30* scene->movementLine_.size(), 30 * scene->movementLine_.size()));
			added_ = true;
		}
		if (ih->getMouseButtonState(InputHandler::LEFT) && movingPointIndex_ == -1)
		{
			auto pos = ih->getMousePos();
			bool found = false;
			int i = 0;
			while (!found && i < scene->movementLine_.size())
			{
				SDL_Rect r= { scene->movementLine_[i].getX() - 15,  scene->movementLine_[i].getY() - 15,30,30 };
				SDL_Point p = { pos.getX(), pos.getY() };
				found = SDL_PointInRect(&p, &r);
				SDL_SetRenderDrawColor(game_->getRenderer(), 0, 255, 0, 255);
				SDL_RenderDrawRect(game_->getRenderer(), &r);
				i++;
			}
			if (found)
				movingPointIndex_ = i-1;
			else
				movingPointIndex_ = -1;
		}
		else if(!(ih->getMouseButtonState(InputHandler::LEFT)))
			movingPointIndex_ = -1;
		if (movingPointIndex_ > -1)
		{
			if (ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::RIGHT))
			{
				scene->movementLine_.erase(scene->movementLine_.begin() + movingPointIndex_);
				movingPointIndex_ = - 1;
			}
			else
			{
				SDL_Rect r = { scene->movementLine_[movingPointIndex_].getX() - 15,  scene->movementLine_[movingPointIndex_].getY() - 15,30,30 };
				SDL_SetRenderDrawColor(game_->getRenderer(), 0, 255, 255, 255);
				SDL_RenderDrawRect(game_->getRenderer(), &r);

				auto pos = ih->getMousePos();
				scene->movementLine_[movingPointIndex_] = pos;
			}
		}
	}
#endif // _DEBUG
}