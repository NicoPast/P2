#include "DragDrop.h"

DragDrop::DragDrop() : Component(ecs::DragDrop), tr_(nullptr) {

}
void DragDrop::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
}
void DragDrop::update() {
	//cout << tr_->getPos() << "||" << tr_->getW() << tr_->getH() << endl;
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		Vector2D pos = ih->getMousePos();
		Vector2D newDragPos = { pos.getX() - tr_->getPos().getX() , pos.getY() - tr_->getPos().getY() };
		if (newDragPos.getX() != dragPos_.getX() && newDragPos.getY() != dragPos_.getY()) {
			Vector2D vel = { newDragPos.getX() - dragPos_.getX(), newDragPos.getY() - dragPos_.getY() };
			tr_->setPos({tr_->getPos().getX() + vel.getX(), tr_->getPos().getY() + vel.getY() });
		}
	}
	else tr_->setVel(0, 0);
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			Vector2D pos = ih->getMousePos();
			SDL_Point p = { pos.getX(), pos.getY() };
			rect = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			if (SDL_PointInRect(&p, &rect)) {
				dragging_ = true;
				dragPos_ = {pos.getX() - rect.x, pos.getY() - rect.y};
			}
		}
	}
	else if (!ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) dragging_ = false;
}