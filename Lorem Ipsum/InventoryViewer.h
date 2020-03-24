#pragma once
#include "Component.h"
#include "SDL_macros.h"
#include "Entity.h"
#include "Transform.h"
class InventoryViewer : public Component
{
public:
	InventoryViewer();
	virtual ~InventoryViewer() {};
	void init();
	void setPistas(vector<Transform*>p) { pistas_ = p; };
	/*void update();*/
	void renderizaPistas(int ini);
private:
	Transform* tr_;
	vector<Transform*> pistas_; // esto no serán Transform sino que serán pistas. Como aún no están hechas por ahora son strings
	bool view_;	// indica si se va a mostrar en pantalla o no el inventario
};

