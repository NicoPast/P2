#include "Scroller.h"

void Scroller::scroll(int speed)
{
	for (auto it : items_) {
		it->setVelX(speed);
	}
}
void Scroller::update() {
	InputHandler* ih = InputHandler::instance();


	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_d)) {
			scroll(scrollSpeed);
		}
		if (ih->isKeyDown(SDLK_a)) {
			scroll(-scrollSpeed);
		}
	}
	else {
		stopScrolling();
	}
	for (auto it : items_) {
		it->addToPosX(it->getVel().getX());
	}
}