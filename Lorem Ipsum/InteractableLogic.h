#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Interactable.h"
#include <list>
#include "Collisions.h"

class InteractableLogic : public Component {
public:
	InteractableLogic(list<Interactable*> inter, Transform* player);
	virtual ~InteractableLogic();
	void init() override;
	void update() override;
private:
	list<Interactable*> inter_;
	Transform* player_;	
};

