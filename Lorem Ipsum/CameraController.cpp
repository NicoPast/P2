#include "CameraController.h"

void CameraController::update()
{
	
	InputHandler* ih = InputHandler::instance();
	Vector2D pos = ih->getMousePos();

	cout << "old position: " << pos.getX() << " " << pos.getY() <<"\n";

	if (ih->mouseButtonEvent() && ih->getMouseButtonState(InputHandler::MOUSEBUTTON::RIGHT))
	{
		cout << "HOLAAAAAAAAAAAAAAAAAAAAAA \n";
		Vector2D newPos = pos - oldPos_;
		cam_->move(newPos);
		cout << newPos.getX() << ", " << newPos.getY() << "\n";
	}
	oldPos_ = pos;

	cout << "old position: " << oldPos_.getX() << " " << oldPos_.getY() << "\n";

}
