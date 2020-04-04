#pragma once
#include "Component.h"
#include "Transform.h"

class Tween :
	public Component
{
public:
	Tween(double x, double y, double speed, double w = -1, double h = -1, bool yoyo = true);
	Tween(Vector2D pos, double speed, double w = -1, double h = -1, bool yoyo = true);
	Tween();
	virtual ~Tween() {};
	void init();
	void update() override;
	void play();
	void stop();

private:
	void changeDir();
	Transform* target_;

	Vector2D intialPos_;
	Vector2D finalPos_;

	double initialW_;
	double initialH_;
	double finalW_;
	double finalH_;

	double speed_;
	double changeW_;
	double changeH_;
	int steps_;

	bool yoyo_;
	bool moving_ = false;
};

