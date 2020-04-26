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
	inline void setTexture(Texture* texture) { texture_ = texture; };
	inline void setAnim(int cols, int rows, Uint32 speed)
	{
		isAnim = true;
		cols_ = cols;
		rows_ = rows;
		animSpeed_ = speed;
		setSourceRect();
	}

	void flipHorizontal(bool flip)
	{

	}
	void flipVertical(bool flip)
	{

	}
private:
	Transform* tr_;
	Texture* texture_;
	SDL_RendererFlip flip_ = SDL_FLIP_NONE;

	void setSourceRect()
	{
		int frameW = (texture_->getWidth() / cols_);
		int frameH = (texture_->getHeight() / rows_);
		sourceRect_ = { actualCol_ * frameW , actualRow_ * frameH, frameW,frameH };
	}
	void advanceAnim()
	{
		if (++actualCol_ >= cols_)
		{
			actualCol_ = 0;
			if(++actualRow_ >= rows_) actualRow_ = 0;
		}
		setSourceRect();
	}
	SDL_Rect sourceRect_;
	Uint32 lastDraw_ = 0;
	Uint32 animSpeed_ = 0;
	int cols_ = 2;
	int rows_ = 0;
	int actualCol_ = 0;
	int actualRow_ = 0;
	bool isAnim=false;
};