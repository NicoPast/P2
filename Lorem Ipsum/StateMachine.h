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
	StateMachine() {};
	~StateMachine();
	void PlayApp(APPS app);
	void PlayGame();
	void PlayMenu();

	State* actualState() { return states_.top(); };

private:
	stack<State*> states_;
	
};

