#pragma once

#include "State.h"

class Options : public State
{
public:
	Options(LoremIpsum* game);
	virtual ~Options() {};

private:
	void init();

	void createBar(int x, int y, int w, int h, string text);
};