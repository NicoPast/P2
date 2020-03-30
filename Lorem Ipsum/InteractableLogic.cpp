#include "InteractableLogic.h"
#include "Entity.h"
#include <math.h>


InteractableLogic::InteractableLogic(list<Interactable*> inter, Transform* player) : Component(ecs::InteractableLogic)
{	inter_ = inter;
	player_ = player;
}

InteractableLogic::~InteractableLogic() {
}

void InteractableLogic::init() {
	
}

void InteractableLogic::update() {
	
	Interactable* nearest = nullptr;
	double nearestDist = NULL;
	for (Interactable* elem : inter_) {
		if (elem->isActive())
		{
			Transform* tr = elem->GetTransform();
			if (Collisions::collidesWithRotation(player_->getPos(), player_->getW(), player_->getH(), player_->getRot(), tr->getPos(), tr->getW(), tr->getH(), tr->getRot()))
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
		other_=nearest->getEntity();
		if(nearest->getOther()==nullptr)nearest->setOther(other_);
	}
}

