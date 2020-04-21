#pragma once
#include "State.h"
#include "PlayState.h"
#include "MainMenu.h"
#include "Chinchetario.h"
#include <stack>


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
	StateMachine(LoremIpsum* g) : game_(g) { playState_ = new PlayState(game_); };
	virtual ~StateMachine() {
		while (actualState() != nullptr) {
			destroyActual();
		}
		if (playState_ != nullptr) delete playState_;
	};
	void PlayApp(APPS app, StoryManager* storyManager=nullptr);
	void PlayGame() { 
		if (states_.size() == 1)
		{
			states_.push(playState_);
			static_cast<PlayState*>(playState_)->init();
		}
		else actualState()->deactivate();
	};
	void PlayMenu() {
		if (states_.size() <= 0)
			states_.push(new MainMenu(game_));
		else actualState()->deactivate();
	};

	State* actualState() { return (!states_.empty()) ? states_.top() : nullptr; };

	void destroyActual() {
		delete actualState();
		if (actualState() == playState_)playState_ = nullptr;
		states_.pop();
		InputHandler::instance()->clearState();
	}
protected:
	stack<State*> states_;
	LoremIpsum* game_ = nullptr;
	State* playState_ = nullptr;

friend class LoremIpsum;
friend class StoryManager;
};

