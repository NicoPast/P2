#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "Text.h"
using callbackInteractbale = void(Entity* player, Entity* other);
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

	void setPlayer(Entity* p) { player_ = p; }
	void setOther(Entity* o) { other_= o; }
	inline Entity* getOther() { return other_; }
	void setCallback(callbackInteractbale cb, Entity* o = nullptr) { f_ = cb; if (o != nullptr)other_ = o; }
private:	
	callbackInteractbale* f_;
	void callback()
	{
		f_(player_, other_);
	}

	//si colisionan estos apuntaran a lo que toque
	Entity* player_=nullptr; 
	Entity* other_= nullptr;

	Transform* tr_;
	bool colliding_;
	bool active_;
	Text* text_;
	string name_;
};

