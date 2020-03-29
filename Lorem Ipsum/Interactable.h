#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Interactable : public Component {
public:
	Interactable();
	virtual ~Interactable();
	void init() override;
	void update() override;
	void changeColl(bool coll) { colliding_ = coll; };
	Transform* GetTransform() { return tr_; };
private:	
	Transform* tr_;
	bool colliding_;
};

