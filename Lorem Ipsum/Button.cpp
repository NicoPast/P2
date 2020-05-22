#include "Button.h"
#include "StoryManager.h"
void Button::init() {
	tr_ = GETCMP1_(Transform);
} 
void Button::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->mouseButtonEvent() && !ih->isLocked()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			Vector2D pos = ih->getMousePos();			//Guarda la posici�n del rat�n
			SDL_Point p = { (int)pos.getX(), (int)pos.getY() };
			rect_ = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
			rect_.x -= xOffset_;
			rect_.y -= yOffset_;
			rect_.w -= wOffset_;
			rect_.h -= hOffset_;
			if (SDL_PointInRect(&p, &rect_)) {			//Si es click dentro del sprite, activa el callback del boton
				SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::ButtonClicked, 0, 1);
				callback();
				ih->mouseButtonHandled();
			}
		}
	}
}

#ifdef _DEBUG 
void Button::draw()
{
	if (StoryManager::instance()->showingHitbox_)
	{
		rect_ = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
		rect_.x -= xOffset_;
		rect_.y -= yOffset_;
		rect_.w -= wOffset_;
		rect_.h -= hOffset_;
		SDL_SetRenderDrawColor(game_->getRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawRect(game_->getRenderer(), &rect_);
	}
}
#endif // 


