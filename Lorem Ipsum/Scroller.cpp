#include "Scroller.h"

void Scroller::scroll(int distance)
{
	for (auto it : items_) {
		it->addToPosX(distance);
	}
}
void Scroller::update() {
	InputHandler* ih = InputHandler::instance();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_d)) {
			scroll(10);
		}
		if (ih->isKeyDown(SDLK_a)) {
			scroll(-10);
		}
	}
	//else {
	//	tr_->setVel(tr_->getVel() * 0.995);
	//}
}