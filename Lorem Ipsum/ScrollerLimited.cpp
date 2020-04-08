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
void ScrollerLimited::addItem(Transform* item, int pos) {
	if (pos > items_.size()) {
		int i = 0;
		auto it = pos_.begin();
		while (it != pos_.end() && *it < pos) {
			++it;
			++i;
		}
		items_.insert(items_.begin() + i, item);
		pos_.insert(pos_.begin() + i, pos);
	}
	else {
		items_.insert(items_.begin() + pos, item);
		pos_.insert(pos_.begin() + pos, pos);
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