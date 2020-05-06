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
	Transform* tr_;
	Uint32 frameTime;
	bool flip = false;
	StoryManager* sm_;
};