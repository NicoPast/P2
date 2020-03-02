#pragma once
#include "Manager.h"



class LoremIpsum;
class State
{
private:
	LoremIpsum* game_;
	EntityManager* enittyManager_;

public:
	void update();
	void render(); 
	void handleInput();
};

