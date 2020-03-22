#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

using CallBackOnClick = void();

class Button :
	public Component
{
public:
	Button(CallBackOnClick f);
	virtual ~Button() {};

	void init();
	void update();
private:
	CallBackOnClick* callback_ = nullptr;
	SDL_Rect rect_;
	Transform* tr_;
};

