#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Text.h"

class Interactable : public Component {
public:
	Interactable(string name, bool active=true);
	virtual ~Interactable();
	void init() override;
	void update() override;
	void changeColl(bool coll) { colliding_ = coll; };
	bool getColl() { return colliding_; };
	Transform* GetTransform() { return tr_; };
	bool isActive() { return active_; };
	void setActive(bool active) { active_ = active; }
private:	
	Transform* tr_;
	bool colliding_;
	bool active_;
	Text* text_;
	string name_;
};

