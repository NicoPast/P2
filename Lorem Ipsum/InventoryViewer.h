#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transform.h"
#include "DragDrop.h"

class Chinchetario; //ESTO ES PROVISIONAL. DEBE ESTAR EN LA ESCENA CHINCHETARIO
class InventoryViewer : public Component
{
public:
	InventoryViewer(Chinchetario* ch);	//CHINCHETARIOOOOOOO
	virtual ~InventoryViewer() {};
	void init();
	void setPistas(vector<Entity*>p) { pistas_ = p; };
	void update();
	void renderizaPistas();
private:
	Transform* tr_;
	vector<Entity*> pistas_; 
	Chinchetario* chinchetario_; //CHINCHETARIOOOOOOO
	SDL_Rect rect_;
	DragDrop* dd_;
	bool view_;	// indica si se va a mostrar en pantalla o no el inventario
	int ini_;
	int index_;
};

