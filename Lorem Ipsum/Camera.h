#pragma once
#include <iostream>
#include "checkML.h"
#include "Vector2D.h"

class Transform;
class SDLGame;

class Camera
{

public:
	Camera(int iniX, int iniY, int leftM, int rightM) :
		x_(iniX), y_(iniY),
		leftMargin_(leftM), rightMargin_(rightM) {};

	bool isObjectInCamera(Transform* tr);
	int inline getPosX() { return x_; };
	int inline getPosY() { return y_; };

	void move(Vector2D vel);

	~Camera() {};

private:
	int x_ = 0, y_ = 0;
	int leftMargin_, rightMargin_;


	static const int CAMERA_WIDTH = 480;
	static const int CAMERA_HEIGHT = 720;
};