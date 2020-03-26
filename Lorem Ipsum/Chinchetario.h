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
	void update();
	void activePista(Entity* p) { activePistas_.push_back(p); }
	void añadePista();
	vector<Entity*>* getPistas_(bool isActive);

private:
	void init();
	vector<Entity*> inactivePistas_;
	vector<Entity*> activePistas_;
	Entity* inv_;
	DragDrop* dd_ = nullptr;
	int dragIndex_;
};

