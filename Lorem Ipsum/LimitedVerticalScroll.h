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
	void addElement(Transform* tr) { 
		elements_.push_back(tr);
		tr->setPosX(elements_[0]->getPos().getX());
		rects_.push_back(GETCMP2(tr->getEntity(), Rectangle));
		texts_.push_back(GETCMP2(tr->getEntity(), Text));
		buts_.push_back(GETCMP2(tr->getEntity(), Button));

		int acumH = 0;
		for (int i = 0; i < elements_.size(); i++) {
			Entity* e_ = elements_[i]->getEntity();
			elements_[i]->setH(GETCMP2(e_, Text)->getCharH() * GETCMP2(e_, Text)->getNumLines());
			texts_[i]->setPos({ texts_[i]->getPos().getX(), texts_[0]->getPos().getY() + acumH });
			elements_[i]->setPosY(elements_[0]->getPos().getY() + acumH);
			acumH += elements_[i]->getH();
		}
	};
	void removeElement(int i)
	{
		i--;
		elements_.erase(elements_.begin() + i);
		texts_.erase(texts_.begin() + i);
		rects_.erase(rects_.begin() + i);
		buts_.erase(buts_.begin()+i);
	}
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