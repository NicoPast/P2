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
	void setPistas(vector<Entity*>p) { pistas_ = p; };
private:
	Transform* tr_;
	vector<Entity*> pistas_; // esto no serán string sino que serán pistas. Como aún no están hechas por ahora son strings
	bool view_;	// indica si se va a mostrar en pantalla o no el inventario
};

