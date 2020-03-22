#pragma once
#include "State.h"
#include "DragDrop.h"
#include "Rectangle.h"
#include "TextTest.h"
#include "Button.h"
#include "Phone.h"
class LoremIpsum;

class PlayState : public State
{
public:
	PlayState(LoremIpsum* game);
	virtual ~PlayState() {  }
private:
	void init();
	static void callbackTest() { cout << "test" << endl; };
};

