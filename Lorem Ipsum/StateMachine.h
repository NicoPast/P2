#pragma once
#include "State.h"
#include "PlayState.h"
#include "Chinchetario.h"
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
	StateMachine(LoremIpsum* g) : game_(g) {};
	virtual ~StateMachine() {};
	void PlayApp(APPS app);
	void PlayGame() { states_.push(new PlayState(game_)); };
	void PlayMenu() {
		if (states_.size() <= 0)
			states_.push(new PlayState(game_));
		else {
			actualState()->deactivate();
		}
	};

	State* actualState() { return states_.top(); };

	void destroyActual() {
		delete actualState();
		states_.pop();
	}
protected:
	stack<State*> states_;
	LoremIpsum* game_ = nullptr;
};

