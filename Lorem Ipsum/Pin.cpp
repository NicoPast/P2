#include "Pin.h"
void Pin::init() {
	l_ = GETCMP1_(Line);
	tr_ = GETCMP1_(Transform);
}
void Pin::update() {
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		Vector2D pos = ih->getMousePos();
		l_->setFin(pos);
	}
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			Vector2D pos = ih->getMousePos();
			SDL_Point p = { pos.getX(), pos.getY() };
			SDL_Rect rect = RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			if (SDL_PointInRect(&p, &rect))
				dragging_ = true;
		}
	}
	else if (!ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) && dragging_) {		//Meter reconocimiento de si ha conectado con otra pista o no
		dragging_ = false;
	}
}