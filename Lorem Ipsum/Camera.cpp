#include "Camera.h"
#include "Transform.h"
#include "Collisions.h"
#include "LoremIpsum.h"
#include "SDLGame.h"


void Camera::move(Vector2D vel)
{
	if (x_ + vel.getX() >= 0 && x_ + width_ + vel.getX() <= SDLGame::instance()->getWindowWidth())
		x_ += vel.getX();

	if (y_ + vel.getY() >= 0 && y_ + height_+ vel.getY() <= SDLGame::instance()->getWindowHeight())
		y_ += vel.getY();
}

bool Camera::isObjectInCamera(Transform* tr)
{
	return Collisions::collides(tr->getPos(), tr->getW(), tr->getH(), pos_, width_, height_);
}

SDL_Rect Camera::getRectToDraw(Transform* tr)
{
	SDL_Rect rect = { tr->getPos().getX() - x_, tr->getPos().getY() - y_, tr->getW(), tr->getH() };
	return rect;
}