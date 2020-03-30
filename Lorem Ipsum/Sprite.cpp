#include "Sprite.h"
#include "SDL_macros.h"
#include "entity.h"
Sprite::Sprite(Texture* texture) : Component(ecs::Sprite), texture_(texture) {}

void Sprite::init()
{
	tr_ = GETCMP1_(Transform);
}
void Sprite::draw()
{
	SDL_Rect destRect = { tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH() };
	if (texture_ != nullptr)
	{
		if(!isAnim)texture_->render(destRect);
		else
		{
			if (game_->getTime()> lastDraw_ + animSpeed_)
			{
				advanceAnim();
				lastDraw_ = game_->getTime();
			}
			texture_->render(destRect, sourceRect_);
		}
	}
}
