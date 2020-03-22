#include "Phone.h"
Phone::Phone() : Component(ecs::Phone), tr_(nullptr) {

}
void Phone::init() {
	SDL_ShowCursor(SDL_ENABLE);
	tr_ = GETCMP1_(Transform);
}

void Phone::update() {
	InputHandler* ih = InputHandler::instance();
	if (moving_) {
		tr_->setPosY(tr_->getPos().getY() + tr_->getVel().getY());
		if (inUse_) {
			if (tr_->getPos().getY() < top_ - speed_)
				stop();
		}
		else if (tr_->getPos().getY()  > bottom_ + speed_)
			stop();
	} else 	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_e)) {
			inUse_ ? move({ 0, speed_ }) : move({ 0, -speed_ });
			moving_ = true;
		}
	}
}

void Phone::move(Vector2D dir)
{
	inUse_ = !inUse_;
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
