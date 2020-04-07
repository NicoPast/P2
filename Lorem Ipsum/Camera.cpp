#include "Camera.h"
#include "Transform.h"
#include "Collisions.h"
#include "LoremIpsum.h"


void Camera::move(Vector2D vel)
{
	if (x_ + vel.getX() >= 0)// || x_ + vel.getX() <= _WINDOW_HEIGHT_)
		x_ += vel.getX();

	if (y_ + vel.getY() >= 0)// || y_ + vel.getY() <= _WINDOW_WIDTH_);
		y_ += vel.getY();
}

bool Camera::IsObjectInCamera(Transform* tr)
{
	Vector2D pos= tr->getPos();
	return (Collisions::PointInRectangle(Vector2D(x_, y_), Vector2D(x_ + CAMERA_WIDTH, y_), Vector2D(x_, y_ + CAMERA_HEIGHT), Vector2D(x_ + CAMERA_WIDTH, y_ + CAMERA_HEIGHT), pos) ||
		Collisions::PointInRectangle(Vector2D(x_, y_), Vector2D(x_ + CAMERA_WIDTH, y_), Vector2D(x_, y_ + CAMERA_HEIGHT), Vector2D(x_ + CAMERA_WIDTH, y_ + CAMERA_HEIGHT), Vector2D(pos.getX + tr->getW(), pos.getY)) ||
		Collisions::PointInRectangle(Vector2D(x_, y_), Vector2D(x_ + CAMERA_WIDTH, y_), Vector2D(x_, y_ + CAMERA_HEIGHT), Vector2D(x_ + CAMERA_WIDTH, y_ + CAMERA_HEIGHT), Vector2D(pos.getX, pos.getY + tr->getH()))) ||
		Collisions::PointInRectangle(Vector2D(x_, y_), Vector2D(x_ + CAMERA_WIDTH, y_), Vector2D(x_, y_ + CAMERA_HEIGHT), Vector2D(x_ + CAMERA_WIDTH, y_ + CAMERA_HEIGHT), Vector2D(pos.getX + tr->getW(), pos.getY + tr->getH()));
}