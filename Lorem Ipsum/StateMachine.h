#pragma once
#include "State.h"
#include "PlayState.h"
#include "MainMenu.h"
#include "DialogEditorState.h"
#include "Chinchetario.h"
#include <stack>
#include "Timeline.h"

class StateMachine
{

public:
	enum APPS : size_t
	{
		MapsApp = 0,
		ChinchetarioApp,
		OptionsApp,
		ContactsApp,
		NotesApp,
		Die,
		lastIconApp,
		// estas 2 apps no se muestran en el movil
        TunerApp,
		TimelineApp,
		lastApps
		
	};
	StateMachine(LoremIpsum* g) : game_(g) { playState_ = new PlayState(game_); };
	virtual ~StateMachine() {
		while (actualState() != nullptr) {
			destroyActual();
		}
		if (playState_ != nullptr) delete playState_;
		if (ch_ != nullptr) delete ch_;
		if (tl_ != nullptr) delete tl_;
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
		else states_.pop();//actualState()->deactivate();
	};
	void PlayEditor() {
		states_.push(new DialogEditorState(game_));
	}

	State* actualState() { return (!states_.empty()) ? states_.top() : nullptr; };
	void destroyActual() {
		if (actualState() != ch_){			//PROVISIONAL  ---	BUSCAR MEJOR MANERA DE GUARDAR CHINCHETARIO
			if(actualState() != tl_)
			delete actualState();
			else actualState()->activate();
        }
		else actualState()->activate();		//PROVISIONAL  ---	BUSCAR MEJOR MANERA DE GUARDAR CHINCHETARIO
		//if (actualState() == playState_)playState_ = nullptr;
		states_.pop();
		//InputHandler::instance()->clearState();
	}


protected:
	stack<State*> states_;
	LoremIpsum* game_ = nullptr;
	State* playState_ = nullptr;
	Chinchetario* ch_ = nullptr;			//PROVISIONAL  ---	BUSCAR MEJOR MANERA DE GUARDAR CHINCHETARIO
	Timeline* tl_ = nullptr;			//PROVISIONAL  ---	BUSCAR MEJOR MANERA DE GUARDAR LA TIMELINE

friend class LoremIpsum;
friend class StoryManager;
};

