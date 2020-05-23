#include "VolumeSlider.h"

void VolumeSlider::init()
{
	int volume;
	if (channel_ == 0)
		volume = game_->getAudioMngr()->setMusicVolume(-1);
	else
		volume = game_->getAudioMngr()->setChannelVolume(-1, channel_);

	//para aujstarlo del rango rango 0-128 al rango minimum_ - maximum_
	volume = (volume * (maximum_ - minimum_) / 128) + minimum_;
	setPos(volume);
}

void VolumeSlider::update()
{
	InputHandler* ih = InputHandler::instance();

	//para saber si el ratón está sobre este slider o no
	Vector2D mouse = ih->getMousePos();
	SDL_Point point = { (int)mouse.getX(), (int)mouse.getY() };
	SDL_Rect rect = game_->getCamera()->getRectToDraw(tr_, entity_->isUI());

	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::LEFT) )
	{
		if(SDL_PointInRect(&point, &rect))
			clicked = true;	
	}
	else clicked = false;

	if (clicked)
	{
		//movemos dependiendo de su horizontalidad y cambiamos el volumen
		Vector2D newPos;
		if (horizontal_)
		{
			newPos = Vector2D(mouse.getX(), 0);
			int x = (int)newPos.getX();
			if (x >= minimum_ && x <= maximum_)
				changeVolume(x);
		}
		else
		{
			newPos = Vector2D(0, mouse.getY());
			int y = (int)newPos.getY();
			if (y >= minimum_ && y <= maximum_)
				changeVolume(y);
		}
	}
	
}

void VolumeSlider::setPos(int value)
{
	if (horizontal_)
		tr_->setPos(value - tr_->getW() / 2, tr_->getPos().getY());
	else
		tr_->setPos(tr_->getPos().getX(), value - tr_->getH() / 2);
}

void VolumeSlider::changeVolume(int val)
{
	//para aujstarlo del rango minimum_ - maximum_  al rango 0-128 

	if (channel_ == 0)
		game_->getAudioMngr()->setMusicVolume(((val - minimum_) * SDL_MIX_MAXVOLUME) / (maximum_ - minimum_));
	else
		game_->getAudioMngr()->setChannelVolume(((val - minimum_) * SDL_MIX_MAXVOLUME) / (maximum_ - minimum_));

	setPos(val);
}
