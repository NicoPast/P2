#pragma once
#include "LoremIpsum.h"
#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"
#include "Bar.h"
#include "Rectangle.h"


class Tuner : public State {
public:
	Tuner(LoremIpsum* game);
	virtual ~Tuner();
	virtual void update() override;
	virtual void render() override;
	void setBars(); //leer las barras desde el story manager?
protected:

private:
	double stress_;
	double maxStress_;
	double stressSpeed_;	//La velocidad de estrés será una media de las velocidades de las barras
	vector<Entity*> bars_;
	bool win_;
};