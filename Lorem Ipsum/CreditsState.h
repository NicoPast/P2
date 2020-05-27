#pragma once
#include "State.h"
class CreditsState :
	public State
{
public:
	CreditsState(LoremIpsum* game);
	virtual ~CreditsState() {  }
	virtual void update() override;
private:
	vector<string> texts;
	Entity* text_ = nullptr;
	int i = 0;
};
