#include "DragDrop.h"

DragDrop::DragDrop() : Component(ecs::DragDrop), tr_(nullptr) {

}
void DragDrop::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
}
void DragDrop::update() {	//Al siguiente frame de estar arrastrando empieza a actualizar su posición
	InputHandler* ih = InputHandler::instance();
	if (dragging_) {
		Vector2D pos = ih->getMousePos();	//Posición del ratón en este frame
		//A partir de aquí hay que pulir
		Vector2D newDragPos = { pos.getX() - tr_->getPos().getX() , pos.getY() - tr_->getPos().getY() };
		if (newDragPos.getX() != dragPos_.getX() && newDragPos.getY() != dragPos_.getY()) {
			Vector2D vel = { newDragPos.getX() - dragPos_.getX(), newDragPos.getY() - dragPos_.getY() };
			tr_->setPos({tr_->getPos().getX() + vel.getX(), tr_->getPos().getY() + vel.getY() });
		}
	}
	else tr_->setVel(0, 0);	//No se si innecesario, pulido también
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {	//¿Parametrizar el botón para configurarlo?
			Vector2D pos = ih->getMousePos();			//Guarda la posición del ratón
			SDL_Point p = { pos.getX(), pos.getY() };
			rect_ = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			if (SDL_PointInRect(&p, &rect_)) {			//Si es click dentro del sprite, activa el drag y guarda su posición relativa
				dragging_ = true;
				dragPos_ = {pos.getX() - rect_.x, pos.getY() - rect_.y};
			}
		}
	}
	else if (!ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) dragging_ = false;
}