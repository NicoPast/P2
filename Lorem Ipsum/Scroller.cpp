#include "Scroller.h"

void Scroller::scroll(int distance)
{
	for (auto it : items_) {
		it->addToPosX(distance);
	}
}
void Scroller::scrollLimited(int distance)
{
	if (items_.front()->getPos().getX() > 0 && distance > 0 ||	//Si el primer elemento está completamente visible
		items_.back()->getPos().getX() <= SDLGame::instance()->getWindowWidth() + items_.back()->getW() && distance < 0) {	//Igual con el ultimo
		for (auto it : items_) {
			it->addToPosX(distance);
		}
	}
}