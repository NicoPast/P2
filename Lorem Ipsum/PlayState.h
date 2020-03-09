#pragma once
#include "State.h"

class LoremIpsum;

class PlayState : public State
{
public:
	PlayState(LoremIpsum* game) : State(game) {};
	virtual ~PlayState() { } // State::~State();
};

