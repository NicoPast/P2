#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "DragDrop.h"

using CallBackOnClick = void(DragDrop* dd); //Provisionalísimo

class Button :
	public Component
{
public:
	Button(CallBackOnClick f, DragDrop* dd);
	virtual ~Button() {};

	void init();
	void update();
private:
	CallBackOnClick* callback_ = nullptr;
	SDL_Rect rect_;
	Transform* tr_;
	DragDrop* dd_; //PROVISIONAL
};

