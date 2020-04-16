#include "Pin.h"
void Pin::init() {
	Drag::init();
	l_ = GETCMP1_(Line);
}
void Pin::update() {
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		Vector2D pos = ih->getMousePos();
		l_->setFin(pos);
	}
	Drag::update();
}