#pragma once

#include "Component.h"
#include "Transform.h"

class PlayerKBCtrl : public Component {
public:
	PlayerKBCtrl();
	PlayerKBCtrl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode rightShift=SDLK_RSHIFT, SDL_Keycode leftShift= SDLK_LSHIFT);
	virtual ~PlayerKBCtrl();

	inline void setCtrlKeys(SDL_Keycode right, SDL_Keycode left, SDL_Keycode rightShift, SDL_Keycode leftShift) {
		right_ = right;
		left_ = left;
		rightShift_ = rightShift;
		leftShift_ = leftShift;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode right_;
	SDL_Keycode left_;
	SDL_Keycode rightShift_;  SDL_Keycode leftShift_;
	Transform* tr_;
	double walkingSpeed = 2.5;
	double runningSpeed = 5;
	double currentSpeed = walkingSpeed;
	double target = NULL;
};
