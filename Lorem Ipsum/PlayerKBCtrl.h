#pragma once

#include "Component.h"
#include "Transform.h"

class PlayerKBCtrl : public Component {
public:
	PlayerKBCtrl();
	PlayerKBCtrl(SDL_Keycode up, SDL_Keycode down, SDL_Keycode stop);
	virtual ~PlayerKBCtrl();

	inline void setCtrlKeys(SDL_Keycode up, SDL_Keycode down,
		SDL_Keycode stop) {
		right_ = up;
		left_ = down;
		stop_ = stop;
	}

	void init() override;
	void update() override;

private:
	SDL_Keycode right_;
	SDL_Keycode left_;
	SDL_Keycode stop_;
	Transform* tr_;
};

