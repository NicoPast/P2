#pragma once
#include "State.h"
#include "PlayState.h"
#include <stack>
class LoremIpsum;


class StateMachine
{

public:
	enum class APPS
	{
		Maps,
		Chinchetario,
		Options,
		Contacts,
	};
	StateMachine(LoremIpsum* g) : game_(g){};
	~StateMachine() {};
	void PlayApp(APPS app) {};
	void PlayGame() { states_.push(new PlayState(game_)); };
	void PlayMenu() { states_.push(new State(game_)); };

	State* actualState() { return states_.top(); };
private:
	stack<State*> states_;
	LoremIpsum* game_=nullptr;
};

