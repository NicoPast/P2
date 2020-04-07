#pragma once
#include <iostream>
#include <SDL.h>
#include "checkML.h"
#include "Vector2D.h"

class Transform;
class SDLGame;

class Camera
{

public:
	Camera(int iniX, int iniY, int leftM, int rightM) :
		x_(iniX), y_(iniY), pos_(iniX, iniY),
		leftMargin_(leftM), rightMargin_(rightM) {
	};
	bool isObjectInCamera(Transform* tr);
	int inline getPosX() { return x_; };
	int inline getPosY() { return y_; };
	int inline getWidth() { return CAMERA_WIDTH; };
	int inline getHeight() { return CAMERA_HEIGHT; };

	void move(Vector2D vel);
	void update() { move(Vector2D(2, 0)); cout << x_ << endl; };
	SDL_Rect getRectToDraw(Transform* tr);

	~Camera() {};

private:
	int x_ = 0, y_ = 0;
	Vector2D pos_;
	int leftMargin_, rightMargin_;


	static const int CAMERA_WIDTH = 480;
	static const int CAMERA_HEIGHT = 720;
};