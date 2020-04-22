#include "Drag.h"
#include "Chinchetario.h"
Drag::Drag(Chinchetario* ch) : Component(ecs::Drag), tr_(nullptr), ch_(ch) {
}
void Drag::init() {
	tr_ = GETCMP1_(Transform);
}
void Drag::update() {
	InputHandler* ih = InputHandler::instance();
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			Vector2D pos = ih->getMousePos();
			SDL_Point p = { pos.getX(), pos.getY() };
			SDL_Rect rect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
			if (SDL_PointInRect(&p, &rect) && ch_->isHigherDragable(this)) {
				if (tr_->getParent() != nullptr) {
					func2();
				}
				dragging_ = true;
				dragPos_ = { rect.x - pos.getX(), rect.y - pos.getY() };
			}
		}
	}
	else if (!ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) && dragging_) {
		dragging_ = false;
		ch_->resetDraggedItem();
		func();
	}
}