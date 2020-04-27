#include "LimitedVerticalScroll.h"
#include "Collisions.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Text.h"

void LimitedVerticalScroll::update()
{
	InputHandler* ih = InputHandler::instance();
	int verticalMotion = ih->getMouseWheelMotion() * 5;

	for (Transform* element : elements_)
	{
		Rectangle* rect = GETCMP2(element->getEntity(), Rectangle);
		Text* text = GETCMP2(element->getEntity(), Text);
		element->setPosY(element->getPos().getY() + verticalMotion);
		text->setPos(text->getPos() + Vector2D(0, verticalMotion));

		if (!Collisions::collides(element->getPos(), element->getW(), element->getH(), Vector2D(limit_.x - tolerance_, limit_.y - tolerance_), limit_.w - tolerance_, limit_.h - tolerance_))
		{
			rect->setEnabled(false);
			text->setEnabled(false);
		}
		else
		{
			rect->setEnabled(true);
			text->setEnabled(true);
		}
	}

};
void LimitedVerticalScroll::draw()
{
	SDL_SetRenderDrawColor(game_->getRenderer(), 255, 120, 0, 255);
	SDL_RenderDrawRect(game_->getRenderer(), &limit_);
}