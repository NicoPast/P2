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
	virtual ~StateMachine() {};
	void PlayApp(APPS app) {};
	void PlayGame() { states_.push(new PlayState(game_)); };
	void PlayMenu() { states_.push(new PlayState(game_)); };

	State* actualState() { return states_.top(); };
protected:
	stack<State*> states_;
	LoremIpsum* game_=nullptr;
};

