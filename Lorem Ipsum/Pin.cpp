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
	if (state_) {
		l_->moveTo(tr_->getPos());
	}
	Drag::update();
}
void Pin::deactivateDrag() {
	Drag::deactivateDrag();
	actualLink_ = nullptr;
	state_ = false;
}