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
	void activePista(Entity* p) { activePistas_.push_back(p); };	//M�TODO QUE DEBE ESTAR EN CHINCHETARIO, NO AQU�
	//--------------------
	vector<Entity*> inactivePistas_; //PARA EL CHINCHETARIO. Pistas que est�n en el inventario
	vector<Entity*> activePistas_;	//PARA EL CHINCHETARIO. Pistas que est�n en el chinchetario
private:
	void init();
};

