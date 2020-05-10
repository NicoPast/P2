#include "InteractableLogic.h"
#include "Entity.h"
#include <math.h>


InteractableLogic::InteractableLogic(list<Interactable*> inter, Transform* player, Transform* iconTR, Sprite* iconRect, ButtonOneParametter<Interactable*>* button) : Component(ecs::InteractableLogic)
{	inter_ = inter;
	player_ = player;
	iconTransform_ = iconTR;
	iconImg_ = iconRect;
	iconButton_ = button;
}

InteractableLogic::~InteractableLogic() {
}	

void InteractableLogic::init() {
	
}

void InteractableLogic::update() {
	
	Interactable* nearest = nullptr;
	double nearestDist = NULL;
	SDL_Rect a = { player_->getPos().getX(), player_->getPos().getY(),player_->getW(), player_->getH() };
	for (Interactable* elem : inter_) {
		if (elem->isEnabled())
		{
			Transform* tr = elem->GetTransform();
			SDL_Rect res;
			SDL_Rect b = { tr->getPos().getX(), tr->getPos().getY(),tr->getW(), tr->getH() };
			/*Nataka Kulia Sana*/
			/*Esto es porque CollidesWithRotation solo comprueba esquinas, si quedan en forma de + no hay col*/
			if(SDL_IntersectRect(&a,&b,&res)||
				/*Esto es por si colisiona con rotación*/
				Collisions::collidesWithRotation(player_->getPos(), player_->getW(), player_->getH(), player_->getRot(), tr->getPos(), tr->getW(), tr->getH(), tr->getRot()))
			{
				if (nearest != nullptr && nearestDist > abs(elem->GetTransform()->getPos().getX() - player_->getPos().getX())) {
					nearest->changeColl(false);
					nearest = elem;
					nearestDist = abs(elem->GetTransform()->getPos().getX() - player_->getPos().getX());
				}
				else if (nearest == nullptr) {

					nearest = elem;
					nearestDist = abs(elem->GetTransform()->getPos().getX() - player_->getPos().getX());
				}
				else elem->changeColl(false);
			}
			else elem->changeColl(false);
		}
	}
	
	if (nearest != nullptr)
	{
		nearest->changeColl(true);
		nearest->setPlayer(player_->getEntity());
		other_ = nearest->getEntity();
		if (nearest->getOther() == nullptr)nearest->setOther(other_);

		if (nearest->isEnabled())
		{
			Transform* nearestTr = nearest->getEntity()->getComponent<Transform>(ecs::Transform);

			iconTransform_->setPosX(nearestTr->getPos().getX() + nearestTr->getW() / 2 - iconTransform_->getW() / 2);
			iconTransform_->setPosY(nearestTr->getPos().getY() - 50);
			
			iconButton_->setEnabled(true);
			iconButton_->setCallback([](Interactable* nearest) {nearest->callback(); }, nearest);
			iconImg_->setEnabled(true);
			iconImg_->setTexture(game_->getTextureMngr()->getTexture(nearest->getEntity()->getComponent<Interactable>(ecs::Interactable)->getIcon()));
		}
	}
	else
	{
		iconImg_->setEnabled(false);
		iconButton_->setEnabled(false);

	}
}

