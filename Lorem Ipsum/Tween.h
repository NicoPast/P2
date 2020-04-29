#pragma once
#include "Component.h"
#include "Transform.h"
#include <functional>
class Tween :
	public Component
{
public:
	Tween(double x, double y, double speed, double w = -1, double h = -1, bool jojo = true);
	Tween(Vector2D pos, double speed, double w = -1, double h = -1, bool jojo = true);
	Tween();
	virtual ~Tween() {};
	void init();
	void update() override;
	void play();
	void GoToA();
	void GoToB();
	void stop();
	void reset();

	Vector2D getDestPos() { return finalPos_; };
	Vector2D getInitalPos() { return intialPos_; };

	void setFunc(function<void(Entity*)> f, Entity* arg) { func_ = f; arg_ = arg; }
	void executeCallback() { if(func_!=nullptr)func_(arg_); }
private:
	void changeDir();
	Transform* target_;

	Vector2D intialPos_;
	Vector2D finalPos_;

	Vector2D a_;
	Vector2D b_;

	double initialW_;
	double initialH_;
	double finalW_;
	double finalH_;

	double wa_;
	double ha_;
	double wb_;
	double hb_;

	double speed_;
	double changeW_;
	double changeH_;
	int steps_;

	bool jojo_;
	bool playing_ = false;

	function<void(Entity*)> func_=nullptr;
	Entity* arg_ = nullptr;
};

