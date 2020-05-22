#pragma once

#include "State.h"

class Options : public State
{
public:
	Options(LoremIpsum* game);
	virtual ~Options() {};

	bool fullscreen = false;

private:
	void init();

	void createBar(int x, int y, int w, int h, int channel, string text, Resources::TextureID icon, SDL_Rect clip);

};