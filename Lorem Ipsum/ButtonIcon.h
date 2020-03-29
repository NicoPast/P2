#pragma once
#include "Button.h"
#include "LoremIpsum.h"

using CallBackOnClick = void(LoremIpsum* game);

class ButtonIcon :
	public Button
{
public:
	ButtonIcon(CallBackOnClick f, LoremIpsum* game) : Button(), f_(f), game_(game) {};
	virtual ~ButtonIcon() {};
private:
	CallBackOnClick* f_;
	virtual void callback() {
		f_(game_);
	}
	LoremIpsum* game_;
};

