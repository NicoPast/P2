#pragma once
#include "State.h"
#include <stack>

enum APPS
{
	Maps,
	Chinchetario,
	Options,
	Contacts,
};

class StateMachine
{
public:
	void PlayApp(APPS app);
	void PlayGame();
	void PlayMenu();

private:
	stack<State*> states_;
	
};

