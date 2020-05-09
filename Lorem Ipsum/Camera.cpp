#include "Camera.h"
#include "Transform.h"
#include "Collisions.h"
#include "LoremIpsum.h"
#include "SDLGame.h"


void Camera::move(Vector2D vel)
{
	if (x_ + vel.getX() >= 0 && x_ + width_ + vel.getX() <= limitX_) {
		x_ += vel.getX();
		pos_.setX(x_);
	}

	if (y_ + vel.getY() >= 0 && y_ + height_ + vel.getY() <= limitY_) {
		y_ += vel.getY();
		pos_.setY(y_);
	}
}

void Camera::move(Transform* tr) {
	double posX = tr->getPos().getX();
	if (posX +tr->getW() > x_ + rightMargin_ && tr->getVel().getX() > 0) {
		move(tr->getVel());
	}
	if (posX < x_ + leftMargin_ && tr->getVel().getX() < 0) {
		move(tr->getVel());
	}
}


bool Camera::isObjectInCamera(Transform* tr)
{
	bool ui = tr->getEntity()->isUI();;
	if(ui)
		return Collisions::collides(tr->getPos()+pos_, tr->getW(), tr->getH(), pos_, width_, height_);
	return Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), pos_, width_, height_);
}

SDL_Rect Camera::getRectToDraw(Transform* tr, bool global)
{
	if (global)
		return SDL_Rect{ (int)(tr->getPos().getX()), (int)(tr->getPos().getY()), (int)(tr->getW()), (int)(tr->getH()) };
	else
		return SDL_Rect{ (int)(tr->getPos().getX() - x_), (int)(tr->getPos().getY() - y_), (int)(tr->getW()), (int)(tr->getH()) };
}
SDL_Rect Camera::getRectToDraw(SDL_Rect& rect, bool global)
{
	if (global)
		return SDL_Rect{rect};
	else
		return SDL_Rect{ rect.x-(int)x_, rect.y-(int)y_, rect.w, rect.h};
}
SDL_Rect Camera::getRectToDraw(Transform* tr)
{
	return getRectToDraw(tr, tr->getEntity()->isUI());
}