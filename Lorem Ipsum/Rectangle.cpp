#include "Rectangle.h"
#include "Entity.h"

Rectangle::Rectangle() :
		Rectangle( { COLOR(0xFFFFFFFF) }) {
}

Rectangle::Rectangle(SDL_Color color) :
		Component(ecs::Rectangle), //
		color_(color), //
		tr_(nullptr) {
}

Rectangle::~Rectangle() {
}

void Rectangle::init() {
	tr_ = GETCMP1_(Transform);
	clip_ = { 0,0,0,0 };
	borderColor_ = {0,0,0,0};
}

void Rectangle::draw() {
	
	if (getEnabled() )
	{
		SDL_Rect rect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
		SDL_Rect result;


		if (clip_.x == 0 && clip_.y==0 && clip_.w==0 && clip_.h==0)
			result = rect;
		else
			SDL_IntersectRect(&rect, &clip_, &result);



		SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
		SDL_RenderFillRect(game_->getRenderer(), &result);

		if (!(borderColor_.r == 0 && borderColor_.g == 0 && borderColor_.b == 0 && borderColor_.a == 0))
		{
			SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(borderColor_));
			SDL_RenderDrawRect(game_->getRenderer(), &result);
		}
	}
}

