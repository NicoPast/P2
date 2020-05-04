#include "VolumeSlider.h"

void VolumeSlider::update()
{
	InputHandler* ih = InputHandler::instance();

	//para saber si el ratón está sobre este slider o no
	Vector2D mouse = ih->getMousePos();
	SDL_Point point = { mouse.getX(), mouse.getY() };
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
			int x = newPos.getX();
			if (x >= minimum_ && x <= maximum_)
				changeVolume(x);
		}
		else
		{
			newPos = Vector2D(0, mouse.getY());
			int y = newPos.getY();
			if (y >= minimum_ && y <= maximum_)
				changeVolume(y);
		}
	}
	
}

void VolumeSlider::changeVolume(int val)
{
	if (horizontal_)
		tr_->setPos(val -tr_->getW()/2, tr_->getPos().getY());
	else
		tr_->setPos(tr_->getPos().getX(), val - tr_->getH()/2);

	if (channel_ == 0)
		game_->getAudioMngr()->setMusicVolume(((val - minimum_) * SDL_MIX_MAXVOLUME) / (maximum_ - minimum_));
	else
		game_->getAudioMngr()->setChannelVolume(((val - minimum_) * SDL_MIX_MAXVOLUME) / (maximum_- minimum_), channel_);
}
