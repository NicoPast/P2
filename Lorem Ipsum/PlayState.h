#pragma once
#include "State.h"
class StoryManager;
class LoremIpsum;

class PlayState : public State
{
public:
	PlayState(LoremIpsum* game);
	virtual ~PlayState() {  }
	void virtual update() override;
private:
	void init();
	StoryManager* sm_;

};
