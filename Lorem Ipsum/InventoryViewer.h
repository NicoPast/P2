#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transform.h"
#include "DragDrop.h"

class Chinchetario; 
class InventoryViewer : public Component
{
public:
	InventoryViewer(Chinchetario* ch);	
	virtual ~InventoryViewer() {};
	void init();
	void setPistas(vector<Entity*>*p) { pistas_ = p; };
	void update();
	void renderizaPistas();
	void sacaPista();
private:
	Transform* tr_;
	vector<Entity*>* pistas_; 
	Chinchetario* chinchetario_; 
	SDL_Rect rect_;
	DragDrop* dd_;
	bool view_;	// indica si se va a mostrar en pantalla o no el inventario
	int ini_;
	int index_;
};

