#include "Sprite.h"
#include "SDL_macros.h"
#include "entity.h"
#include "Collisions.h"
Sprite::Sprite(Texture* texture) : Component(ecs::Sprite), texture_(texture) {}

void Sprite::init()
{
	tr_ = GETCMP1_(Transform);
	if (texture_)
		sourceRect_ = { 0, 0, texture_->getWidth(), texture_->getHeight() };
	else sourceRect_ = { 0, 0, 0, 0 };
}
void Sprite::draw()
{
	if (texture_ != nullptr)
	{
		if (game_->getCamera()->isObjectInCamera(tr_))
		{
			SDL_Rect destRect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());

			texture_->setColorMod(r_, g_, b_);
			texture_->render(destRect, tr_->getRot(), sourceRect_);
			texture_->setColorMod(255, 255, 255);
		}

	}
}
