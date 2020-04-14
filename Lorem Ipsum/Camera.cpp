#include "Camera.h"
#include "Transform.h"
#include "Collisions.h"
#include "LoremIpsum.h"
#include "SDLGame.h"


void Camera::move(Vector2D vel)
{
	if (x_ + vel.getX() >= 0 && x_ + width_ + vel.getX() <= 2000) {
		x_ += vel.getX();
		pos_.setX(x_);
	}

	if (y_ + vel.getY() >= 0 && y_ + height_ + vel.getY() <= SDLGame::instance()->getWindowHeight()) {
		y_ += vel.getY();
		pos_.setY(y_);
	}
}

bool Camera::isObjectInCamera(Transform* tr)
{
	return Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), pos_, width_, height_);
}

SDL_Rect Camera::getRectToDraw(Transform* tr, bool global)
{
	if (global)
		return SDL_Rect{ (int)(tr->getPos().getX() - x_), (int)(tr->getPos().getY() - y_), (int)(tr->getW()), (int)(tr->getH()) };
	else
		return SDL_Rect{ (int)(tr->getPos().getX() + x_), (int)(tr->getPos().getY() + y_), (int)(tr->getW()), (int)(tr->getH()) };

}