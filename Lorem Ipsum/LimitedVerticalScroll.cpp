#include "LimitedVerticalScroll.h"
#include "Collisions.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Text.h"
#include "Button.h"

void LimitedVerticalScroll::update()
{
	InputHandler* ih = InputHandler::instance();
	int verticalMotion = ih->getMouseWheelMotion() * 5;

	bool firstOut = elements_[0]->getPos().getY()+verticalMotion < limit_.y;
	bool lastOut = elements_.back()->getPos().getY() + elements_.back()->getH() + verticalMotion > limit_.y + limit_.h;

	bool firstBorder = elements_[0]->getPos().getY() + verticalMotion >= limit_.y;
	bool lastBorder = elements_.back()->getPos().getY() + elements_.back()->getH() + verticalMotion <= limit_.y + limit_.h;
	

	if ((firstOut && lastBorder && verticalMotion <0)||(lastOut&&firstBorder && verticalMotion > 0) )
		verticalMotion = 0;


	for (Transform* element : elements_)
	{
		Rectangle* rect = GETCMP2(element->getEntity(), Rectangle);
		Text* text = GETCMP2(element->getEntity(), Text);
		Button* but = GETCMP2(element->getEntity(), Button);
		
		element->setPosY(element->getPos().getY() + verticalMotion);
		text->setPos(text->getPos() + Vector2D(0, verticalMotion));
		SDL_Rect res;
		elementRect_.x = element->getPos().getX();
		elementRect_.y = element->getPos().getY();
		SDL_IntersectRect(&elementRect_, &limit_, &res);
		
		rect->setClip(res);
		text->setEnabled(res.h > 20);
		but->setEnabled(res.h > 20);
	}

};
void LimitedVerticalScroll::draw()
{
	if (!showBar)return;
	int w = 2;
	int x = 1;
	SDL_SetRenderDrawColor(game_->getRenderer(), barColor_.r, barColor_.g, barColor_.b, barColor_.a);
	for(int i =0; i<w;i++)
		SDL_RenderDrawLine(game_->getRenderer(), i+x+ limit_.x + limit_.w, limit_.y, i+x+limit_.x + limit_.w, limit_.y + limit_.h);
	SDL_SetRenderDrawColor(game_->getRenderer(), indicatorColor_.r, indicatorColor_.g, indicatorColor_.b, indicatorColor_.a);

	double barH = limit_.h;
	double totalH = elementRect_.h * elements_.size();
	double scale = totalH/barH;
	int indicatorH = elementRect_.h *2 /scale;
	int indicatorY = (elements_[0]->getPos().getY() - limit_.y) / -scale;
	for (int i = 0; i < w; i++)
		SDL_RenderDrawLine(game_->getRenderer(), i+x+limit_.x + limit_.w, limit_.y + indicatorY, i+x+limit_.x + limit_.w, limit_.y + indicatorY+indicatorH);

}
void LimitedVerticalScroll::init()
{
	elementRect_ = { (int)elements_[0]->getPos().getX(), (int)elements_[0]->getPos().getY(), (int)elements_[0]->getW(),(int)elements_[0]->getH() };
}
