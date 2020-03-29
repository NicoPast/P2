#pragma once
#include "State.h"

class LoremIpsum;

class PlayState : public State
{
public:
	PlayState(LoremIpsum* game);
	virtual ~PlayState() {  }
private:
	void init();

};
