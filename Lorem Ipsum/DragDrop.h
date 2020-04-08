#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
class Chinchetario;
using CallBackDD = void(Chinchetario*, Entity*);


class DragDrop : public Component
{
public:
	DragDrop(Chinchetario* ch, CallBackDD* cb);
	~DragDrop() {};
	void init() override;
	void update() override;
	bool getDragging() { return dragging_; }
	void deactivateDrag() { dragging_ = false; }
	//PROVISIONALES
	//void setTxt(string t) { txtprovisional_ = t; }
	//string getTxt() { return txtprovisional_; }
private:
	void func() { f_(ch_, entity_); }

	CallBackDD* f_;
	Transform* tr_;
	SDL_Rect rect_;					//No se si deber�amos guardarlo
	bool dragging_ = false;			//Si est� arrastrando
	Vector2D dragPos_ = { 0, 0 };	//Distancia del lugar de clic a la esquina superior izquierda
	Chinchetario* ch_;					
	bool lastInLayer_ = false;		//Evitar parpadeo
	//string txtprovisional_;			//PROVISIONAL. NECESITAMOS STORY MANAGER PORFAPLIS
};

