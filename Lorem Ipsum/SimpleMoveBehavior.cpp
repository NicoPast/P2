#include "SimpleMoveBehavior.h"
#include "Entity.h"


void SimpleMoveBehavior::init()
{
	tr_ = GETCMP1_(Transform);
}
void SimpleMoveBehavior::update()
{
	if (tr_->getVel().getX() == 0 && tr_->getVel().getY() == 0)
		return;
	tr_->setPos(tr_->getPos() + tr_->getVel());
	if (target.getY()!=-1.0 && tr_->getPos().magnitude() >= target.magnitude())
	{
		tr_->setVel(0.0, 0.0);
		if (f_)
			f_();
	}
}
void SimpleMoveBehavior::moveTo(Vector2D pos, int speed)
{
	target = pos;
	tr_->setVel((pos - tr_->getPos()).normalize() *speed);
}


/*

A -------> B
A <------- B

*/