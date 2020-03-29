#include "ScrollerLimited.h"

void ScrollerLimited::scroll(int speed)
{
	if (items_.size() > 0 &&	//Si el vector no esta vacio
		items_.front()->getPos().getX() > minX_ && speed < 0 ||	//Si el primer elemento está completamente visible
		items_.back()->getPos().getX() < maxX_ - items_.back()->getW() && speed > 0) {	//Igual con el ultimo
		Scroller::scroll(speed);
	}
}
void ScrollerLimited::update() {
	InputHandler* ih = InputHandler::instance();

	if (ih->mouseButtonEvent()) {
		if (ih->getMouseWheelMotion() == 1) {
			scroll(scrollSpeed);
		}
		else if (ih->getMouseWheelMotion() == -1) {
			scroll(-scrollSpeed);
		}
		else {
			stopScrolling();
		}
	}
	else {
		stopScrolling();
	}
	for (auto it : items_) {
		it->addToPosX(it->getVel().getX());
	}
}