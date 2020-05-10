#pragma once

#include <SDL_rect.h>
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include "Transform.h"

class Rectangle: public Component {
public:
	Rectangle();
	Rectangle(SDL_Color color);
	virtual ~Rectangle();
	void init() override;
	void draw() override;
	inline void setEnabled(bool e) { enabled_ = e; };
	inline bool getEnabled() { return enabled_; }
	inline void setColor(SDL_Color c) { color_ = c; }
	inline void setBorder(SDL_Color c) { borderColor_ = c; }
	inline void setClip(SDL_Rect clip) { clip_ = clip; }
private:
	SDL_Color color_;
	SDL_Color borderColor_;
	SDL_Rect clip_ = {};
	Transform *tr_ = nullptr;
	bool enabled_ = true;
};

