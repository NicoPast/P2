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
	cout << posX + width_ - rightMargin_ << endl;
	if (posX > x_ + rightMargin_ && posX + width_ - rightMargin_ <= limitX_) {	//ese 2000 se refiere al tamaño de la escena, deberia pillarlo del storymanager
		x_ = posX - rightMargin_;
	}
	if (posX < x_ + leftMargin_ && posX - leftMargin_ >= 0) {
		x_ = posX - leftMargin_;
	}
	pos_.setX(x_);
}


bool Camera::isObjectInCamera(Transform* tr)
{
	return Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), pos_, width_, height_);
}

SDL_Rect Camera::getRectToDraw(Transform* tr, bool global)
{
	if (global)
		return SDL_Rect{ (int)(tr->getPos().getX()), (int)(tr->getPos().getY()), (int)(tr->getW()), (int)(tr->getH()) };
	else
		return SDL_Rect{ (int)(tr->getPos().getX() - x_), (int)(tr->getPos().getY() - y_), (int)(tr->getW()), (int)(tr->getH()) };
}