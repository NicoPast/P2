#pragma once
#include <vector>
#include "Transform.h"
#include "ecs.h"
#include "Scroller.h"

class ScrollerLimited : public Scroller
{
public:
	ScrollerLimited() {}
	ScrollerLimited(int maxX, int minX): maxX_(maxX), minX_(minX) {}
	virtual ~ScrollerLimited() {}
	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	virtual void scroll(int speed);

	virtual void stopScrolling() { Scroller::scroll(0); }
	virtual void update();
private:
	int maxX_ = SDLGame::instance()->getWindowWidth();
	int minX_ = 0;
};