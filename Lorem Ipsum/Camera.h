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
	Camera(int iniX, int iniY, int width , int height,  int leftM, int rightM) :
		x_(iniX), y_(iniY), pos_(iniX, iniY),
		leftMargin_(leftM), rightMargin_(width - rightM) {
	};
	bool isObjectInCamera(Transform* tr);
	double inline getPosX() { return x_; };
	double inline getPosY() { return y_; };
	int inline getWidth() { return width_; };
	int inline getHeight() { return height_; };
	int inline getLeftMargin() { return leftMargin_; };
	int inline getRightMargin() { return rightMargin_; };


	void move(Vector2D vel);
	void update() {cout << x_ + width_ << endl; };
	SDL_Rect getRectToDraw(Transform* tr, bool global);

	~Camera() {};

private:
	double x_ = 0, y_ = 0;
	Vector2D pos_;
	int leftMargin_, rightMargin_;
	int width_ =1080, height_ = 720;
};