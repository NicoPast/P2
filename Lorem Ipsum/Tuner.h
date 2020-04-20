#pragma once
#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"
#include "Bar.h"

class Tuner : public State {
public:
	Tuner(LoremIpsum* game, int n);
	virtual ~Tuner();
	virtual void update() override;
	virtual void render() override;
	void setBars(vector<Bar*> b) { bars = b; }
protected:

private:
	int nBars;
	double heat;
	double maxHeath;
	vector<Bar*> bars;
};