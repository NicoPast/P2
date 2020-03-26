#pragma once
#include "State.h"
#include "Rectangle.h";
#include "InventoryViewer.h"
class LoremIpsum;

class Chinchetario : public State
{
public:
	Chinchetario(LoremIpsum* game);
	virtual ~Chinchetario() {  }
	void activePista(Entity* p) { activePistas_.push_back(p); };	//MÉTODO QUE DEBE ESTAR EN CHINCHETARIO, NO AQUÍ
	//--------------------
	vector<Entity*> inactivePistas_; //PARA EL CHINCHETARIO. Pistas que están en el inventario
	vector<Entity*> activePistas_;	//PARA EL CHINCHETARIO. Pistas que están en el chinchetario
private:
	void init();
};

