#include "Sprite.h"
#include "SDL_macros.h"
#include "entity.h"
#include "Collisions.h"
Sprite::Sprite(Texture* texture) : Component(ecs::Sprite), texture_(texture) {}

void Sprite::init()
{
	tr_ = GETCMP1_(Transform);
}
void Sprite::draw()
{
	if (texture_ != nullptr)
	{
		if (game_->getCamera()->isObjectInCamera(tr_))
		{
			SDL_Rect destRect = game_->getCamera()->getRectToDraw(tr_, isUI());

			if (!isAnim)texture_->render(destRect);
			else
			{
				if (game_->getTime() > lastDraw_ + animSpeed_)
				{
					advanceAnim();
					lastDraw_ = game_->getTime();
				}
				texture_->render(destRect, sourceRect_);
			}
		}
	}
}
