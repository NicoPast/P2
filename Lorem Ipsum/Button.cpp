#include "Button.h"

void Button::init() {
	tr_ = GETCMP1_(Transform);
} 
void Button::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			Vector2D pos = ih->getMousePos();			//Guarda la posición del ratón
			SDL_Point p = { pos.getX(), pos.getY() };
			rect_ = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
			rect_.x -= xOffset_;
			rect_.y -= yOffset_;
			rect_.w -= wOffset_;
			rect_.h -= hOffset_;
			if (SDL_PointInRect(&p, &rect_)) {			//Si es click dentro del sprite, activa el callback del boton
				callback();
				ih->mouseButtonHandled();
			}
		}
	}
}
