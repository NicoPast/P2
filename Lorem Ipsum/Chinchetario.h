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
private:
	void init();
};

