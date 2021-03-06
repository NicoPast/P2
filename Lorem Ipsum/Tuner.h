#pragma once
#include "LoremIpsum.h"
#include "State.h"
#include "StoryManager.h"
#include "ButtonOneParametter.h"
#include "ScrollerLimited.h"
#include "Bar.h"
#include "Rectangle.h"
#include "Sprite.h"


class Tuner : public State {
public:
	Tuner(LoremIpsum* game);
	virtual ~Tuner() {}
	virtual void update() override;
	virtual void render() override;
	void setBars(); //leer las barras desde el story manager?
	void increaseStressSpeed(double amount) { stressSpeed_ += amount; };
	void changeStressDir(double dir);

	void setGhost(Resources::ActorID ghost) { ghost_ = ghost; };
private:
	void createStressMeter();
	double stress_ = 0;
	double maxStress_ = 0;
	double stressSpeed_ = 0;	//La velocidad de estr�s ser� una media de las velocidades de las barras
	int direction_ = 1;
	vector<Entity*> bars_;
	//int delay;

	int numVictorias = 0;
	int numDerrotas = 0;

	double angle_ = 0;
	double radius_ = 0;
	Resources::ActorID ghost_;
	Vector2D stressCenter_ = Vector2D();
	Transform* stresTr_ = nullptr;
	Sprite* stresCalm_ = nullptr;

};