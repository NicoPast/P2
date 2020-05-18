#include "LimitedVerticalScroll.h"
#include "Collisions.h"
#include "Transform.h"
#include "Entity.h"
#include "Rectangle.h"
#include "Text.h"
#include "Button.h"
#ifdef _DEBUG
#include "StoryManager.h"
#endif

void LimitedVerticalScroll::update()
{
	InputHandler* ih = InputHandler::instance();
	double barH = limit_.h;
	double totalH = 0;
	for (int i = 0; i < elements_.size(); i++) {
		totalH += (double)elements_[i]->getH();
	}
	SDL_Point cursor = SDL_Point{ (int)ih->getMousePos().getX(), (int)ih->getMousePos().getY() };
	if (totalH > barH && SDL_PointInRect(&cursor, &limit_)) {
		int verticalMotion = ih->getMouseWheelMotion() * 5;

		bool firstOut = elements_[0]->getPos().getY() + verticalMotion < limit_.y;
		bool lastOut = elements_.back()->getPos().getY() + elements_.back()->getH() + verticalMotion > limit_.y + limit_.h;

		bool firstBorder = elements_[0]->getPos().getY() + verticalMotion >= limit_.y;
		bool lastBorder = elements_.back()->getPos().getY() + elements_.back()->getH() + verticalMotion <= limit_.y + limit_.h;

		if (!(firstOut && lastBorder && verticalMotion < 0) && !(lastOut && firstBorder && verticalMotion > 0))
		{
			for (int i = 0; i < elements_.size(); i++)
			{
				elements_[i]->setPosY(elements_[i]->getPos().getY() + verticalMotion);
				texts_[i]->setPos(texts_[i]->getPos() + Vector2D(0, verticalMotion));
				SDL_Rect res;
				elementRect_.x = (int)elements_[i]->getPos().getX();
				elementRect_.y = (int)elements_[i]->getPos().getY();
				elementRect_.w = (int)elements_[i]->getW();
				elementRect_.h = (int)elements_[i]->getH();
				SDL_IntersectRect(&elementRect_, &limit_, &res);

				rects_[i]->setClip(res);
				texts_[i]->setEnabled(res.h > 20 /*&& texts_[i]->getNumLines() * texts_[i]->getCharH() <= res.h*/);
				buts_[i]->setEnabled(res.h > 20);
			}
		}
	}
};
void LimitedVerticalScroll::draw()
{
	double barH = limit_.h;
	double totalH = 0;
	for (int i = 0; i < elements_.size(); i++) {
		totalH += (double)elements_[i]->getH();
	}
	double scale = (totalH > barH) ? totalH / barH : 1;
	if (!showBar)return;
	int w = 2;
	int x = 1;
	SDL_SetRenderDrawColor(game_->getRenderer(), barColor_.r, barColor_.g, barColor_.b, barColor_.a);
	for(int i =0; i<w;i++)
		SDL_RenderDrawLine(game_->getRenderer(), i+x+ limit_.x + limit_.w, limit_.y, i+x+limit_.x + limit_.w, limit_.y + limit_.h);
	SDL_SetRenderDrawColor(game_->getRenderer(), indicatorColor_.r, indicatorColor_.g, indicatorColor_.b, indicatorColor_.a);

	int grow = (int)(limit_.h / (totalH / elements_.size()));
	int indicatorH = 0;
	for (int i = 0; i < elements_.size(); i++) {
		indicatorH += elements_[i]->getH() * grow;
	}
	indicatorH /= elements_.size();
	indicatorH /= scale;
	int indicatorY = (elements_[0]->getPos().getY() - limit_.y) / -scale;
	for (int i = 0; i < w; i++)
		SDL_RenderDrawLine(game_->getRenderer(), i+x+limit_.x + limit_.w, limit_.y + indicatorY, i+x+limit_.x + limit_.w, limit_.y + indicatorY+indicatorH);
	
#ifdef _DEBUG
	if (!StoryManager::instance()->showingHitbox_)
	{
		SDL_SetRenderDrawColor(game_->getRenderer(), 0, 255, 0, 255);
		SDL_RenderDrawRect(game_->getRenderer(), &limit_);
	}
#endif // DEBUG
}
void LimitedVerticalScroll::init()
{
	for (Transform* element : elements_)
	{
		rects_.push_back(GETCMP2(element->getEntity(), Rectangle));
		texts_.push_back(GETCMP2(element->getEntity(), Text));
		buts_.push_back(GETCMP2(element->getEntity(), Button));
	}
	int acumH = 0;
	for (int i = 0; i < elements_.size(); i++) {
		Entity* e_ = elements_[i]->getEntity();
		elements_[i]->setH(GETCMP2(e_, Text)->getCharH() * GETCMP2(e_, Text)->getNumLines());
		texts_[i]->setPos({ texts_[i]->getPos().getX(), texts_[0]->getPos().getY() + acumH });
		elements_[i]->setPosY(elements_[0]->getPos().getY() + acumH);
		acumH += elements_[i]->getH();
	}
	elementRect_ = { (int)elements_[0]->getPos().getX(), (int)elements_[0]->getPos().getY(), (int)elements_[0]->getW(),(int)elements_[0]->getH() };
}
