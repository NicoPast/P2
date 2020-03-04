#pragma once
#include "State.h"

class LoremIpsum;
class PlayState : public State
{
	PlayState(LoremIpsum* game) : State(game) {};
	~PlayState() { State::~State(); }
};

