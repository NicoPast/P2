#pragma once
#include "State.h"
#include "StoryManager.h"
class LoremIpsum;

class PlayState : public State
{
public:
	PlayState(LoremIpsum* game);
	virtual ~PlayState() {}
	void virtual update() override;
	//StoryManager* getStoryManager() { return sm_.get(); };
	void init();
private:
	//unique_ptr<StoryManager>sm_;
	//StoryManager* 
};
