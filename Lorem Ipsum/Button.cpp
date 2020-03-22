#include "Button.h"

Button::Button(CallBackOnClick f) : Component(ecs::Button), tr_(nullptr), callback_(f) {

}
void Button::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
} 
void Button::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			Vector2D pos = ih->getMousePos();			//Guarda la posición del ratón
			SDL_Point p = { pos.getX(), pos.getY() };
			rect_ = SDL_Rect RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
			if (SDL_PointInRect(&p, &rect_)) {			//Si es click dentro del sprite, activa el callback del boton
				callback_();
			}
		}
	}
}
