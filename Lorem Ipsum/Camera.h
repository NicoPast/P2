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
	Camera(int iniX = 0, int iniY = 0, int width = 1280, int height = 720,  int leftM = 0, int rightM = 0) :
		x_(iniX), y_(iniY), pos_(iniX, iniY),
		leftMargin_(leftM), rightMargin_(width - rightM), width_(width), height_(height) {
	};
	bool isObjectInCamera(Transform* tr);
	
	double inline getPosX() { return x_; };
	double inline getPosY() { return y_; };
	void inline setPosX(double x) { x_ = x; pos_.setX(x); };
	void inline setPosY(double y) { y_ = y; pos_.setY(y); };

	int inline getWidth() { return width_; };
	int inline getHeight() { return height_; };
	void inline setWidth(double x) { width_ = (int)x; };
	void inline setHeight(double y) { height_ = (int)y; };

	int inline getLeftMargin() { return leftMargin_; };
	int inline getRightMargin() { return rightMargin_; };
	void inline setLeftMargin(double left) { leftMargin_ = (int)left; };
	void inline setRightMargin(double right) { rightMargin_ = width_ - (int)right; };

	Vector2D inline getPos() { return pos_; };
	void inline setPos(Vector2D v) { pos_ = v; x_ = v.getX(); y_ = v.getY(); };
	void inline setPos(double x, double y) { x_ = (int)x; y_ = (int)y; pos_.setX(x); pos_.setY(y); };

	double inline getLimitX() { return limitX_; };
	double inline getLimitY() { return limitY_; };
	//para cambiar los límites del mundo a los que puede llegar la cámara
	void inline setLimitX(double newLimit) { limitX_ = (int)newLimit; };
	//para cambiar los límites del mundo a los que puede llegar la cámara
	void inline setLimitY(double newLimit) { limitY_ = (int)newLimit; };


	void move(Vector2D vel);
	void move(Transform* tr);
	void update() {};

	//llamar siempre en el draw. No crear el rectángulo de destino manualmente.
	SDL_Rect getRectToDraw(Transform* tr, bool global);
	SDL_Rect getRectToDraw(SDL_Rect& tr, bool global);
	SDL_Rect getRectToDraw(Transform* tr);

	~Camera() {};

private:
	double x_ = 0, y_ = 0;
	Vector2D pos_ = Vector2D(0, 0);
	int leftMargin_ = 0, rightMargin_ = 0;		//márgenes a la izquierda y derecha para que la cámara empiece a moverse
	int width_ =1080, height_ = 720;			//ancho y alto de la cámara
	int limitX_ = 2000;							//límite del mundo a lo ancho. Puede ser diferente para cada escena
	int limitY_= 2000;							//límite del mundo a lo alto. Puede ser diferente para cada escena
};