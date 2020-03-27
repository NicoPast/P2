#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
class DragDrop : public Component
{
public:
	DragDrop();
	~DragDrop() {};
	void init() override;
	void update() override;
	bool getDragging() { return dragging_; }
private:
	Transform* tr_;
	SDL_Rect rect_;					//No se si deber�amos guardarlo
	bool dragging_ = false;			//Si est� arrastrando
	Vector2D dragPos_ = { 0, 0 };	//Posici�n relativa del lugar de agarre
};

