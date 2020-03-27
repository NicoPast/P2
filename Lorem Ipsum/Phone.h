#pragma once
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
class Phone :
	public Component
{
public:
	Phone();
	virtual ~Phone() {};

	void init();
	void initIcons(vector<Transform*> icons) { icons_ = icons; };
	void update();
private:
	void move(Vector2D dir);
	void stop();

	bool inUse_ = false;
	bool moving_ = false;
	double top_ = 200;
	double bottom_ = 480;
	double speed_ = 9;
	Transform* tr_;
	vector<Transform*> icons_;
};

