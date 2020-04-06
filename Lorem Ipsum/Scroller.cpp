#include "Scroller.h"

void Scroller::scroll(int speed)
{
	if (!items_.empty())
	{
		for (auto it : items_) {
            it->setVelX(speed);
		}
		
	}

}
void Scroller::update() {
	InputHandler* ih = InputHandler::instance();


	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_RIGHT) && player_->getPos().getX() + player_->getW() >= rightBound_) {
			scroll(-scrollSpeed);
		}
		if (ih->isKeyDown(SDLK_LEFT) && player_->getPos().getX() <= leftBound_) {
			scroll(scrollSpeed);
		}
	}
	else {
		stopScrolling();
	}
	for (auto it : items_) {
		it->addToPosX(it->getVel().getX());
	}
}