#include "Phone.h"
Phone::Phone() : Component(ecs::Phone), tr_(nullptr) {

}
void Phone::init(){
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
	top_ = game_->getWindowHeight() - tr_->getH();
	bottom_ = game_->getWindowHeight();
}

void Phone::update() {
	InputHandler* ih = InputHandler::instance();
	if (moving_) {
		tr_->setPosY(tr_->getPos().getY() + tr_->getVel().getY());
		for (int i = 0; i < icons_.size(); i++)
		{
			icons_[i]->setPosY(icons_[i]->getPos().getY() + icons_[i]->getVel().getY());;
		}
		if (inUse_) {
			if (tr_->getPos().getY() < top_ - speed_)
				stop();
		}
		else if (tr_->getPos().getY()  > bottom_ + speed_)
			stop();
	} else 	if (ih->keyDownEvent() ) 
	{
		if (ih->isKeyDown(SDLK_s) && inUse_) {
			move({ 0, speed_ });
			inUse_ = false;
			moving_ = true;
		}
		else if(ih->isKeyDown(SDLK_w) && !inUse_) {
			move({ 0, -speed_ });
			inUse_ = true;
			moving_ = true;
		}
	}
}

void Phone::move(Vector2D dir)
{
	tr_->setVel(dir);
	for (int i = 0; i < icons_.size(); i++)
	{
		icons_[i]->setVel(dir);
	}
}

void Phone::stop()
{
	tr_->setVel({ 0, 0 });
	for (int i = 0; i < icons_.size(); i++)
	{
		icons_[i]->setVel({ 0, 0 });
	}
	moving_ = false;
}
