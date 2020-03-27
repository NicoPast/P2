#pragma once
#include "State.h"
#include "DragDrop.h"
#include "Rectangle.h"
#include "Button.h"
#include "Phone.h"
#include "Scroller.h"
#include "ScrollerLimited.h"
#include "PlayerKBCtrl.h"
#include "PlayerMovement.h"
#include "Text.h"
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
	static void callbackTest0() { cout << "test0" << endl; };
	static void callbackTest1() { cout << "test1" << endl; };
	static void callbackTest2() { cout << "test2" << endl; };

};
