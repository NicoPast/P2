#include "ScrollerLimited.h"


void ScrollerLimited::scroll(int speed) {
	for (auto it : items_) {
		it->setVelX(speed);
	}
}
void ScrollerLimited::scrollLimited(int speed)
{
	if (items_.size() > 0)// &&	//Si el vector no esta vacio
	{
		if (speed > 0 && items_.front()->getPos().getX() < minX_ ||	//Si el primer elemento está completamente visible
			speed < 0 && items_.back()->getPos().getX() > maxX_ - items_.back()->getW()) //Igual con el ultimo
		{
			scroll(speed);
		}
	}
}

void ScrollerLimited::stopScrolling() {
	scroll(0);
}


void ScrollerLimited::update() {
	InputHandler* ih = InputHandler::instance();

	if (ih->getMouseWheelMotion() != 0) {
		scrollLimited(scrollSpeed * ih->getMouseWheelMotion());	//Cambia la velocidad de todos los transform segun la rueda del raton
	}
	else {
		stopScrolling();
	}
	for (auto it : items_) {
		it->addToPosX(it->getVel().getX());	//Mueve todos los objetos
	}
}