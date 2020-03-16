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
	~PlayState() { State::~State(); }
private:
	void init();
};

