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
		
		//si ha llegado a un límite se para
		if ((tr_->getPos().getY() < top_ - speed_ && inUse_) || (tr_->getPos().getY() > bottom_ + speed_) && !inUse_)
			stop();
		//si no se mueve
		else
		{
			tr_->setPosY(tr_->getPos().getY() + tr_->getVel().getY());
			for (int i = 0; i < icons_.size(); i++)
			{
				icons_[i]->setPosY(icons_[i]->getPos().getY() + icons_[i]->getVel().getY());;
			}
		}
	} 
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
