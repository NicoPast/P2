#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include <list>
class PlayState;
class DragDrop : public Component
{
public:
	DragDrop(PlayState* ps);
	~DragDrop() {};
	void init() override;
	void update() override;
	void deactivateDrag() { dragging_ = false; }
private:
	Transform* tr_;
	SDL_Rect rect_;					//No se si deberíamos guardarlo
	bool dragging_ = false;			//Si está arrastrando
	Vector2D dragPos_ = { 0, 0 };	//Distancia del lugar de clic a la esquina superior izquierda
	PlayState* ps_;					//CAMBIAR POR CHINCHETARIO
	bool lastInLayer_ = false;		//Evitar parpadeo
};

