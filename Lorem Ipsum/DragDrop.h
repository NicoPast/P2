#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
class DragDrop : public Component
{
public:
	DragDrop();
	~DragDrop() {};
	void init() override;
	void update() override;
private:
	Transform* tr_;
	SDL_Rect rect;
	bool dragging_ = false;
	Vector2D dragPos_ = { 0, 0 };
};

