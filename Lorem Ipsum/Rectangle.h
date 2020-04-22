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
private:
	SDL_Color color_;
	Transform *tr_;
	bool enabled_ = true;
};

