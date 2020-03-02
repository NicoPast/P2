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
private:
	void initGame() { game_= SDLGame::init("YEAH, BOI",_WINDOW_WIDTH_, _WINDOW_HEIGHT_); };
	void closeGame() { delete game_; };
	void handleInput();
	void update();
	void render();


private:
	SDLGame* game_;
	StateMachine* states_;
	bool exit_;
	
	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};

