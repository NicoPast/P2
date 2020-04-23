#pragma once
#include "Component.h"
#include "Transform.h"
#include "Resources.h"
#include <functional>
#include "Entity.h"

template<typename... Targs>
using callback = void* (Targs...);


template<typename T>
class Animator : public Component
{
public:
	Animator() : Component(ecs::Animator)
	{
	}
	~Animator() {};

	void init() override
	{
		transform_ = GETCMP1_(Transform);
	};
	void draw() override {
		

		if (actualAnimInfo_ != nullptr)
		{
			if (game_->getTime() - lastDraw_ >= actualAnimInfo_->speed_)
			{
				lastDraw_ = game_->getTime();
				actualFrame_++;
				executeCallback(arg_);

				if (actualFrame_ >= actualAnimInfo_->lastFrame_)
				{
					actualFrame_ = (actualAnimInfo_->loop_) ? actualAnimInfo_->initialFrame_ : actualAnimInfo_->lastFrame_;
				}
				updateAnim();
			}
			SDL_Rect destRect{ transform_->getPos().getX(), transform_->getPos().getY(), transform_->getW(), transform_->getH() };
			text_->render(destRect, sourceRect_);
		}
	};
	void changeAnim(Resources::AnimID id)
	{
		actualAnimID_ = id;
		actualAnimInfo_ = &Resources::anims_[id];
		actualFrame_ = actualAnimInfo_->initialFrame_;
		text_ = game_->getTextureMngr()->getTexture(actualAnimInfo_->textureId_);
		//text_->setBlendingMode(SDL_BLENDMODE_NONE);
		updateAnim();
	};

	Resources::AnimID getAnim() { return actualAnimID_; };

	void setFunc(std::function<void(T)> cb, T args)
	{
		func_ = cb;
		arg_ = args;
	}
private:
	Resources::AnimID    actualAnimID_= Resources::AnimID::LastAnimID;
	Resources::AnimInfo *actualAnimInfo_ = nullptr;
	size_t lastDraw_=0;
	int actualFrame_=0;
	Transform *transform_;

	void updateAnim()
	{
		rows_ = actualFrame_ / actualAnimInfo_->cols_;
		cols_ = actualFrame_ % actualAnimInfo_->cols_;
		w_ = text_->getWidth() / actualAnimInfo_->cols_;
		h_ = text_->getHeight() / actualAnimInfo_->rows_;
		sourceRect_ = { cols_ * w_, rows_ * h_,w_,h_ };

	};

	void executeCallback(T margs)
	{
		if (func_ != nullptr)
			func_(margs);
	}

	SDL_Rect sourceRect_;
	Texture* text_ = nullptr;;
	int w_ =-1;
	int h_ = -1;
	int rows_ = -1;
	int cols_ = -1;
	callback<>* cb_ = nullptr;


	std::function<void(T)> func_ = nullptr;
	T arg_;
};
