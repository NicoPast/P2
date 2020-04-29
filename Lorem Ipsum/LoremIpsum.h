#pragma once
#include "SDLGame.h"
#include "StateMachine.h"

class LoremIpsum
{
public:
	LoremIpsum();
	virtual ~LoremIpsum() { closeGame(); };

	void start(); //Empieza el gameloop
	void stop() { exit_ = true; };
	SDLGame* getGame() { return game_; };
	StateMachine* getStateMachine() { return states_; };
	StoryManager* getStoryManager() { return story_; }
	void changeScene(Resources::SceneID id);


private:
	void initGame();
	void closeGame() { delete states_; delete story_; };
	void handleInput();
	void update();
	void render();


private:
	SDLGame* game_;
	StateMachine* states_;
	StoryManager* story_;

	bool exit_;
	
	const static int _WINDOW_WIDTH_ = 1280;
	const static int _WINDOW_HEIGHT_ = 720;

};

