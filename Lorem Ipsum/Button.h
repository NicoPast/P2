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

#ifdef _DEBUG
	virtual void draw();
#endif // _DEBUG


	//guarda un offset para el transform del button
	virtual void setOffsets(int hitboxX, int hitboxY, int hitboxW, int hitboxH) {
		xOffset_ = hitboxX; 
		yOffset_ = hitboxY;
		wOffset_ = hitboxW;
		hOffset_ = hitboxH;
	};
protected:
	virtual void callback() {};
	SDL_Rect rect_ = {};
	Transform* tr_ = nullptr;
	int xOffset_=0;
	int yOffset_=0;
	int wOffset_=0;
	int hOffset_=0;
};