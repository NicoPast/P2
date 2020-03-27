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