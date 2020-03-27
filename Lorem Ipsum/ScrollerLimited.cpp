#include "ScrollerLimited.h"

void ScrollerLimited::scroll(int distance)
{
	if (items_.front()->getPos().getX() > 0 && distance < 0 ||	//Si el primer elemento está completamente visible
		items_.back()->getPos().getX() < SDLGame::instance()->getWindowWidth() - items_.back()->getW() && distance > 0) {	//Igual con el ultimo
		Scroller::scroll(distance);
	}
}