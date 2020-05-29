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
		//te refieres a este metodo flipHorizontal o a otro
		texture_->flipHorizontal(isflipH_);
		texture_->flipVertical(isflipV_);
		SDL_Rect destRect;
		if (!ignoreCamera_ && game_->getCamera()->isObjectInCamera(tr_))
		{
			destRect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());
		}
		else if(ignoreCamera_){
			destRect={ (int)tr_->getPos().getX(), (int)tr_->getPos().getY(), (int)tr_->getW(), (int)tr_->getH() };
		}
		texture_->setColorMod(r_, g_, b_);
		texture_->render(destRect, tr_->getRot(), sourceRect_);
		SDL_RenderDrawRect(game_->getRenderer(),&destRect);
		texture_->setColorMod(255, 255, 255);

		if (showSubtexture_)
		{
			subTexture_->render(destRect,tr_->getRot(), sourceRect_);
		}
		if (!(borderColor_.r == 0 && borderColor_.g == 0 && borderColor_.b == 0 && borderColor_.a == 0))
		{
			SDL_SetRenderDrawColor(game_->getRenderer(), COLOREXP(borderColor_));
			SDL_RenderDrawRect(game_->getRenderer(), &destRect);
		}
		/*isflipH_ = false; isflipV_ = false;*/
		texture_->flipHorizontal(false);
		texture_->flipVertical(false);
		
	}
}
