#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transform.h"
#include "DragDrop.h"
#include "ScrollerLimited.h"

class Chinchetario; 
class InventoryViewer : public Component
{
public:
	InventoryViewer(Chinchetario* ch);	
	virtual ~InventoryViewer() {};
	void init();
	void setPistas(vector<Entity*>* p) { pistas_ = p; if (pistas_->size() > 5)
		{
		for (int i = 5; i<pistas_->size(); i++)
			{ 
				(*pistas_)[i]->setActive(false); 
			}; 
		}; 
	};
	void update();
	void renderizaPistas(int ini = 0);
	void sacaPista();
private:
	Transform* tr_;
	vector<Entity*>* pistas_;	 //vector con las pistas
	Chinchetario* chinchetario_; //escena
	SDL_Rect thisRect_;				 //rect del inventario
	DragDrop* dd_;
	bool view_;	// indica si se va a mostrar en pantalla o no el inventario
	int ini_;
	int index_;
};

