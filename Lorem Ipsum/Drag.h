#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
class Chinchetario;

class Drag : public Component {
public:
	Drag(Chinchetario* ch);
	~Drag() {};
	void init() override;
	void update() override;
	bool getDragging() { return dragging_; }
	Vector2D getDragPos() { return dragPos_; }
	virtual void deactivateDrag() { dragging_ = false; }
protected:
	virtual void func() {}
	virtual void func2() {}
	Transform* tr_;
	Chinchetario* ch_;
	bool dragging_ = false;
	Vector2D dragPos_;
};