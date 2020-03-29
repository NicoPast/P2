#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Button :
	public Component
{
public:

	Button() : Component(ecs::Button), tr_(nullptr){};
	virtual ~Button() {};

	void init();
	virtual void update();
protected:
	virtual void callback() { cout << "lol\n"; };
	SDL_Rect rect_;
	Transform* tr_;
};