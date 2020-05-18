#pragma once
#include "Component.h"
#include "Rectangle.h"
#include "Transform.h"
#include "Text.h"
#include "Button.h"
#include "checkML.h"

class LimitedVerticalScroll : public Component
{
public:
	LimitedVerticalScroll(SDL_Rect limit, vector<Transform*> elements, double tolerance, SDL_Color barColor, SDL_Color indicatorColor) : 
		Component(ecs::LimitedVerticalScroll), limit_(limit), tolerance_(tolerance),elements_(elements),barColor_(barColor),indicatorColor_(indicatorColor)
	{

	}
	virtual ~LimitedVerticalScroll(){}

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;
	virtual void show() { showBar = true; };
	virtual void hide() { showBar = false; };
	void addElement(Rectangle* r, Transform* tr, Button* but, Text* text) { elements_.push_back(tr), rects_.push_back(r), buts_.push_back(but), texts_.push_back(text); };
private:
	SDL_Rect limit_ = {};
	SDL_Rect elementRect_ = {};
	SDL_Color barColor_;
	SDL_Color indicatorColor_;
	int firstElementOffset_ = 0;
	bool showBar = false;

	vector<Transform*> elements_;
	vector<Rectangle*> rects_;
	vector<Text*> texts_;
	vector<Button*> buts_;
	double tolerance_ = 0;
};