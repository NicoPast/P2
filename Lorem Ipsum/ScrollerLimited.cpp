#include "ScrollerLimited.h"

void ScrollerLimited::scroll(int distance)
{
	if (items_.front()->getPos().getX() > 0 && distance < 0 ||	//Si el primer elemento está completamente visible
		items_.back()->getPos().getX() < SDLGame::instance()->getWindowWidth() - items_.back()->getW() && distance > 0) {	//Igual con el ultimo
		Scroller::scroll(distance);
	}
}
void ScrollerLimited::update() {
	InputHandler* ih = InputHandler::instance();

	if (ih->mouseButtonEvent()) {
		if (ih->getMouseWheelMotion() == 1) {
			scroll(10);
		}
		else if (ih->getMouseWheelMotion() == -1) {
			scroll(-10);
		}
	}
	//else {
	//	tr_->setVel(tr_->getVel() * 0.995);
	//}
}