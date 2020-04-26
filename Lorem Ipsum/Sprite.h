#pragma once
#include "Component.h"
#include "Transform.h"
class Sprite
	: public Component
{
public:
	Sprite(Texture* texture);
	virtual ~Sprite() {};
	virtual void draw() override;
	virtual void init() override;
	inline void setTexture(Texture* texture) { texture_ = texture; sourceRect_ = { 0, 0, texture_->getWidth(), texture_->getHeight() }; };
	inline void setSourceRect(SDL_Rect clip) { sourceRect_ = clip; };

private:
	Transform* tr_;
	Texture* texture_;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;

	SDL_Rect sourceRect_;
};