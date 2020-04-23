#include "Pin.h"
void Pin::init() {
	Drag::init();
	Entity* e = entity_->getEntityMangr()->addEntity(entity_->getLayer());
	l_ = e->addComponent<Line>(tr_->getPos(), tr_->getPos(), 4);
	e->setUI(true);
}
void Pin::update() {
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		Vector2D pos = ih->getMousePos();
		l_->setFin(pos + game_->getCamera()->getPos());
	}
	//Si está enganchado a algo, actualiza la posición de la línea
	if (state_) {
		Vector2D newpos = { tr_->getW() / 2, tr_->getH() / 2 };
		newpos = tr_->getPos() + newpos;
		l_->moveTo(newpos);
	}
	Drag::update();
}
void Pin::deactivateDrag() {
	Drag::deactivateDrag();
	actualLink_ = nullptr;
	state_ = false;
}
//true si está conectado a algo y su id es igual a la correcta
bool Pin::isCorrect() {
	bool correct = false;
	if (actualLink_ != nullptr) {
		correct = actualLink_->id_ == correctLink_;
	}
	return correct;
}