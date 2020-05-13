#include "Sprite.h"
#include "SDL_macros.h"
#include "entity.h"
#include "Collisions.h"
#include "SDLGame.h"
#ifdef _DEBUG
#include "StoryManager.h"
#endif
Sprite::Sprite(Texture* texture) : Component(ecs::Sprite), texture_(texture) {}

Sprite::Sprite() :Component(ecs::Sprite)
{
	texture_ = nullptr;
}

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
		if (!ignoreCamera_ && game_->getCamera()->isObjectInCamera(tr_))
		{
			SDL_Rect destRect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
#ifdef _DEBUG
			if (StoryManager::instance()->chopMovement_)
			{
				destRect.x -= destRect.x % 8;
				destRect.y -= destRect.y % 8;
			}
#endif // _DEBUG
			texture_->setColorMod(r_, g_, b_);
			texture_->render(destRect, tr_->getRot(), sourceRect_);
			texture_->setColorMod(255, 255, 255);
		}
		else if(ignoreCamera_){
			SDL_Rect destRect = { (int)tr_->getPos().getX(), (int)tr_->getPos().getY(), (int)tr_->getW(), (int)tr_->getH() };
#ifdef _DEBUG
			if (StoryManager::instance()->chopMovement_)
			{
				destRect.x -= destRect.x % 8;
				destRect.y -= destRect.y % 8;
			}
#endif // _DEBUG
			texture_->setColorMod(r_, g_, b_);
			texture_->render(destRect, tr_->getRot(), sourceRect_);
			texture_->setColorMod(255, 255, 255);
		}

	}
}
