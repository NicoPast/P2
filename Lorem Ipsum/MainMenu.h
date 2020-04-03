#pragma once
#include "State.h"
class MainMenu :
	public State
{
public:
	MainMenu(LoremIpsum* game);
	virtual ~MainMenu() {  }
private:
	void init();
	static void soyUnEnfermo();
};

