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
	a_ = intialPos_;
	b_ = finalPos_;
	wa_ = initialW_;
	ha_ = initialH_;
	wb_ = finalW_;
	hb_ = finalH_;
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
		Vector2D aux = a_;
		a_ = b_;
		b_ = aux;

		double auxd;

		if (wb_ != -1) {
			auxd = wa_;
			wa_ = wb_;
			wb_ = auxd;
		}

		if (hb_ != -1) {
			auxd = ha_;
			ha_ = hb_;
			hb_ = auxd;
		}
	}
	else {
		target_->setPos(a_);
		target_->setWH(wa_, ha_);
	}

	target_->setVel((b_ - a_).normalize() * speed_);
	
	playing_ = true;

	steps_ = (int)((abs((target_->getPos() - b_).magnitude())) / speed_);
	if (steps_ == 0) {
		if (round(changeW_) != 0)
			steps_ = (int)abs((wb_ - wa_) / speed_);
		else steps_ = (int)abs((hb_ - ha_) / speed_);
		stop();
	}

	changeW_ = (wb_ - target_->getW()) / steps_;
	changeH_ = (hb_ - target_->getH()) / steps_;
}

void Tween::stop()
{
	target_->setPos(b_);
	target_->setVel({ 0,0 });
	playing_ = false;
	if(target_->getPos().getX() == finalPos_.getX() && target_->getPos().getY() == finalPos_.getY())
		executeCallback();
}

void Tween::play()
{
	changeDir();
}

// only if it has jojo = true
void Tween::GoToA() {
	if (jojo_ && ((b_.getX() != intialPos_.getX() || b_.getY() != intialPos_.getY()) || wb_ != initialW_ || hb_ != initialH_))
		changeDir();
}

// only if it has jojo = true
void Tween::GoToB() {
	if (jojo_ && ((b_.getX() != finalPos_.getX() || b_.getY() != finalPos_.getY()) || wb_ != finalW_ || hb_ != finalH_))
		changeDir();
}
