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
private:
	Transform* tr_;
	SDL_Rect rect_;					//No se si deber�amos guardarlo
	bool dragging_ = false;			//Si est� arrastrando
	Vector2D dragPos_ = { 0, 0 };	//Distancia del lugar de clic a la esquina superior izquierda
};

