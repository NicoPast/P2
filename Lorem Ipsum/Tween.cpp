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
	jojo_(yoyo)
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
	changeDir();
	playing_ = false;
}

void Tween::update()
{
	if (playing_) {
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
	if (jojo_)
	{
		Vector2D aux = intialPos_;
		intialPos_ = finalPos_;
		finalPos_ = aux;

		double auxd;

		if (finalW_ != -1) {
			auxd = initialW_;
			initialW_ = finalW_;
			finalW_ = auxd;
		}

		if (finalH_ != -1) {
			auxd = initialH_;
			initialH_ = finalH_;
			finalH_ = auxd;
		}
	}
	else {
		target_->setPos(intialPos_);
		target_->setWH(initialW_, initialH_);
	}

	target_->setVel((finalPos_ - intialPos_).normalize() * speed_);
	
	playing_ = true;

	steps_ = (abs((target_->getPos() - finalPos_).magnitude())) / speed_;
	if (steps_ == 0) {
		if (round(changeW_) != 0)
			steps_ = abs((finalW_ - initialW_) / speed_);
		else steps_ = abs((finalH_ - initialH_) / speed_);
	}

	changeW_ = (finalW_ - target_->getW()) / steps_;
	changeH_ = (finalH_ - target_->getH()) / steps_;
}

void Tween::stop()
{
	target_->setPos(finalPos_);
	target_->setVel({ 0,0 });
	playing_ = false;
}

void Tween::play()
{
	changeDir();
}
