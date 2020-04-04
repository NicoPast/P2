#include "Tween.h"
#include "Entity.h"

Tween::Tween(double x, double y, double speed, double w, double h, bool yoyo) : Tween(Vector2D{x, y}, speed, w, h, yoyo)
{
}

Tween::Tween(Vector2D pos, double speed, double w, double h, bool yoyo) :
	Component(ecs::Tween), 
	finalPos_(pos), 
	finalW_(w),	
	finalH_(h),
	speed_(speed),
	yoyo_(yoyo)
{
}

Tween::Tween() : Tween(0,0,0)
{
}

void Tween::init()
{
	target_ = GETCMP1_(Transform);
	intialPos_ = target_->getPos();
	initialW_ = target_->getW();
	initialH_ = target_->getH();
}

void Tween::update()
{
	if (moving_) {
		if (steps_ <= 0) {
			stop();
		}
		else {
			if(finalW_ != -1)
				target_->setW(target_->getW() + changeW_);
			if (finalH_ != -1)
				target_->setH(target_->getH() + changeH_);
			target_->setPos(target_->getPos() + target_->getVel());
			steps_--;
		}
	}
}

void Tween::changeDir()
{	
	changeW_ = (finalW_ - initialW_) / speed_;
	changeH_ = (finalH_ - initialH_) / speed_;

	if (yoyo_)
	{
		Vector2D aux = intialPos_;
		intialPos_ = finalPos_;
		finalPos_ = aux;
	}
	else {
		target_->setPos(intialPos_);
	}
	target_->setVel((finalPos_ - intialPos_).normalize() * speed_);
	moving_ = true;

	double distance = abs((target_->getPos() - finalPos_).magnitude());
	steps_ = distance / speed_;
}

void Tween::stop()
{
	target_->setPos(finalPos_);
	target_->setVel({ 0,0 });
	moving_ = false;
}

void Tween::play()
{
	changeDir();
}
