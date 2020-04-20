#include "Phone.h"
Phone::Phone() : Component(ecs::Phone), tr_(nullptr) {

}
void Phone::init(){
	tr_ = GETCMP1_(Transform);
	top_ = game_->getWindowHeight() - tr_->getH();
	bottom_ = game_->getWindowHeight();
}

void Phone::update() {
}

void Phone::move(bool up)
{
	setDir({ 0, ((up)? -speed_ : speed_)});
	inUse_ = up;
	moving_ = true;

}

void Phone::setDir(Vector2D dir)
{
	tr_->setVel(dir);
	for (int i = 0; i < icons_.size(); i++)
	{
		icons_[i]->setVel(dir);
	}
}

void Phone::stop()
{
	setDir({ 0,0 });
	moving_ = false;
}
