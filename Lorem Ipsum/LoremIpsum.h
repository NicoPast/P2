#pragma once
#include "SDLGame.h"
#include "StateMachine.h"

class LoremIpsum : public Singleton<LoremIpsum>
{
friend class Singleton<LoremIpsum>;
public:
	virtual ~LoremIpsum() { closeGame(); };
	void start(); //Empieza el gameloop
	void stop() { exit_ = true; };
	SDLGame* getGame() { return game_; };
	StateMachine* getStateMachine() { return states_; };
	StoryManager* getStoryManager() { return story_; }
	void changeScene(Resources::SceneID id);


private:
	LoremIpsum();

	void initGame();
	void closeGame() { delete states_;};
	void handleInput();
	void update();
	void render();


private:
	SDLGame* game_ = nullptr;
	StateMachine* states_ = nullptr;
	StoryManager* story_ = nullptr;

	bool exit_ = false;
	
	const static int _WINDOW_WIDTH_ = 1280;
	const static int _WINDOW_HEIGHT_ = 720;

};

