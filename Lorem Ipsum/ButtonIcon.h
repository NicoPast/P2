#pragma once
#include "Button.h"
#include "LoremIpsum.h"
#include "StoryManager.h"

using CallBackLI = void(LoremIpsum* game, StoryManager* sm);

class ButtonIcon :
	public Button
{
public:
	ButtonIcon(CallBackLI f, LoremIpsum* game, StoryManager* sm = nullptr) : Button(), f_(f), game_(game), sm_(sm) {};
	virtual ~ButtonIcon() {};
private:
	CallBackLI* f_;
	virtual void callback() {
		f_(game_,sm_);
	}
	LoremIpsum* game_;
	StoryManager* sm_;
};

