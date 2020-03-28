#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
class Chinchetario;
class DragDrop : public Component
{
public:
	DragDrop(Chinchetario* ch);
	~DragDrop() {};
	void init() override;
	void update() override;
	bool getDragging() { return dragging_; }
	void deactivateDrag() { dragging_ = false; }
private:
	Transform* tr_;
	SDL_Rect rect_;					//No se si deber�amos guardarlo
	bool dragging_ = false;			//Si est� arrastrando
	Vector2D dragPos_ = { 0, 0 };	//Distancia del lugar de clic a la esquina superior izquierda
	Chinchetario* ch_;					
	bool lastInLayer_ = false;		//Evitar parpadeo
};

