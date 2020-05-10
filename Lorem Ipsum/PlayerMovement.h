#pragma once

#include "Component.h"
#include "Transform.h"
class StoryManager;
class PlayerMovement : public Component {
public:
	PlayerMovement(StoryManager* sm);
	virtual ~PlayerMovement();
	void init() override;
	void update() override;
	void draw() override;
private:
	void perspective(Vector2D& dir);
	Transform* tr_ = nullptr;
	Uint32 frameTime = 0;
	bool flip = false;
	StoryManager* sm_ = nullptr;
};