#include "VolumeSlider.h"

void VolumeSlider::update()
{
	InputHandler* ih = InputHandler::instance();
	if (ih->mouseButtonEvent()) {
		if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT)) {
			
			//para saber si el ratón está sobre este slider o no
			Vector2D mouse = ih->getMousePos();
			SDL_Point point = { mouse.getX(), mouse.getY() };
			SDL_Rect rect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
			if (SDL_PointInRect(&point, &rect))
			{
				//movemos dependiendo de su horizontalidad y cambiamos el volumen
				Vector2D newPos;
				if (horizontal_)
				{
					newPos = tr_->getPos() + Vector2D(mouse.getX, 0);
					moveHorizontally(newPos);
				}
				else
				{
					newPos = tr_->getPos() + Vector2D(0, mouse.getY());
					moveVertically(newPos);
				}

			}/**/
		}
	}
}

void VolumeSlider::moveHorizontally(Vector2D whereTo)
{
	int y = whereTo.getY();
	if (y >= minimum_ && y <= maximum_) tr_->setPosY(y);
}

void VolumeSlider::moveVertically(Vector2D whereTo)
{
}
