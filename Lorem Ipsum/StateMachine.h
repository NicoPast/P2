#pragma once
#include "State.h"
#include <stack>
class LoremIpsum;
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
	StateMachine(LoremIpsum* g) : game_(g){};
	~StateMachine() {};
	void PlayApp(APPS app) {};
	void PlayGame() {};
	void PlayMenu() { states_.push(new State(game_)); };

	State* actualState() { return states_.top(); };
private:
	stack<State*> states_;
	LoremIpsum* game_=nullptr;
};

