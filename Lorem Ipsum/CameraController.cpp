#include "CameraController.h"

void CameraController::update()
{
	//game_->getCamera()->move(Vector2D(2, 0));

	InputHandler* ih = InputHandler::instance();
	Vector2D pos = ih->getMousePos();
	
	if (ih->getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT))
	{
		Vector2D newPos = pos - oldPos_;
		game_->getCamera()->move(newPos *(-1));

	}

	oldPos_ = pos;
}
