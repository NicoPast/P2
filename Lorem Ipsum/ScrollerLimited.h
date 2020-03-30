#pragma once
#include <vector>
#include "Transform.h"
#include "ecs.h"
#include "Scroller.h"

class ScrollerLimited : public Scroller
{
public:
	ScrollerLimited() {
		maxX_ = SDLGame::instance()->getWindowWidth();
		minX_ = 0;
	}
	ScrollerLimited(int minX, int maxX): maxX_(maxX), minX_(minX) {}
	virtual ~ScrollerLimited() {}
	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	virtual void scroll(int speed);

	virtual void stopScrolling() { Scroller::scroll(0); }
	virtual void update();
private:
	int maxX_;
	int minX_;
};