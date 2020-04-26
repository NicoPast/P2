#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Interactable.h"
#include <list>
#include "Collisions.h"
#include "Sprite.h"
#include "Rectangle.h"
#include "ButtonOneParametter.h"

class InteractableLogic : public Component {
public:
	InteractableLogic(list<Interactable*> inter, Transform* player, Transform* iconTR, Sprite* iconRect, ButtonOneParametter<Interactable*>* button);
	virtual ~InteractableLogic();
	void init() override;
	void update() override;
private:
	list<Interactable*> inter_;
	Transform* player_;	
	Entity* other_;
	Sprite* iconImg_;			//el icono que sale para interactuar con el ratón
	Transform* iconTransform_;	//el transform del icono
	ButtonOneParametter<Interactable*>* iconButton_;

};

