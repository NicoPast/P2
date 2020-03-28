#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"
#include "DragDrop.h"
#include "Text.h"

using CallBackOnClick = void(DragDrop* dd, Text* t); //Provisionalísimo

class Button :
	public Component
{
public:
	Button(CallBackOnClick f, DragDrop* dd, Text* t);
	virtual ~Button() {};

	void init();
	void update();
private:
	CallBackOnClick* callback_ = nullptr;
	SDL_Rect rect_;
	Transform* tr_;
	DragDrop* dd_; //PROVISIONAL
	Text* t_;
};

