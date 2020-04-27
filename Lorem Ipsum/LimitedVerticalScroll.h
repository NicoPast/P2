#pragma once
#include "Component.h"

class LimitedVerticalScroll : public Component
{
public:
	LimitedVerticalScroll(SDL_Rect limit, vector<Transform*> elements, double tolerance) : Component(ecs::LimitedVerticalScroll), limit_(limit), tolerance_(tolerance),elements_(elements)
	{

	}
	virtual ~LimitedVerticalScroll(){}

	virtual void update() override;
	virtual void draw() override;

private:
	SDL_Rect limit_;
	vector<Transform*> elements_;
	double tolerance_;
};