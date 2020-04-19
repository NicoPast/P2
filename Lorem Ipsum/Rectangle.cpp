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
}

void Rectangle::draw() {
	
	if (getEnabled())
	{
		SDL_Rect rect = game_->getCamera()->getRectToDraw(tr_, isUI());

		SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(color_));
		SDL_RenderFillRect(game_->getRenderer(), &rect);
	}

}

