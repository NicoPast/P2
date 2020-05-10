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
	Transform* target_ = nullptr;

	Vector2D intialPos_ = Vector2D();
	Vector2D finalPos_ = Vector2D();

	Vector2D a_ = Vector2D();
	Vector2D b_ = Vector2D();

	double initialW_ = 0;
	double initialH_ = 0;
	double finalW_ = 0;
	double finalH_ = 0;

	double wa_ = 0;
	double ha_ = 0;
	double wb_ = 0;
	double hb_ = 0;

	double speed_ = 0;
	double changeW_ = 0;
	double changeH_ = 0;
	int steps_ = 0;

	bool jojo_ = false;
	bool playing_ = false;

	function<void(Entity*)> func_=nullptr;
	Entity* arg_ = nullptr;
};

