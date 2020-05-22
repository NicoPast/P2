#include "SimpleMoveBehavior.h"
#include "Entity.h"


void SimpleMoveBehavior::init()
{
	tr_ = GETCMP1_(Transform);
}
void SimpleMoveBehavior::update()
{
	tr_->setPos(tr_->getPos() + tr_->getVel());
}

