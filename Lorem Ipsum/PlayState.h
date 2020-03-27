#pragma once
#include "State.h"
#include "DragDrop.h"
#include "Rectangle.h"
#include "TextTest.h"
class LoremIpsum;

class PlayState : public State
{
public:
	PlayState(LoremIpsum* game);
	virtual ~PlayState() {  }
	bool compareDragItemIndex(int index, int layer);		//TRASPASAR A QUIEN MANEJE LOS DRAG (Chinchetario)
	void resetDragItemIndex() { dragItemIndex = -1; }		//TRASPASAR A QUIEN MANEJE LOS DRAG (Chinchetario)
private:
	void init();
	int dragItemIndex = -1;									//Objeto arrastrandose segun su capa
};

