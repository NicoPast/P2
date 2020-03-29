#pragma once
#include "Button.h"
#include "LoremIpsum.h"

using CallBackLI = void(LoremIpsum* game);

class ButtonIcon :
	public Button
{
public:
	ButtonIcon(CallBackLI f, LoremIpsum* game) : Button(), f_(f), game_(game) {};
	virtual ~ButtonIcon() {};
private:
	CallBackLI* f_;
	virtual void callback() {
		f_(game_);
	}
	LoremIpsum* game_;
};

