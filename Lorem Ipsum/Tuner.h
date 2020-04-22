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
	virtual ~Tuner() {}
	virtual void update() override;
	virtual void render() override;
	void setBars(); //leer las barras desde el story manager?
protected:

private:
	void createStressMeter();
	double stress_;
	double maxStress_;
	double stressSpeed_;	//La velocidad de estr�s ser� una media de las velocidades de las barras
	vector<Entity*> bars_;
	//int delay;

	int test = 0;
	double angle_ = 0;
	double radius_ = 0;
	Vector2D stressCenter_;
	Transform* stresTr_ = nullptr;
};