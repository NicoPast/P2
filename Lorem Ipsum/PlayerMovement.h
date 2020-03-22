#pragma once

#include "Component.h"
#include "Transform.h"

class PlayerMovement : public Component {
public:
	PlayerMovement();
	virtual ~PlayerMovement();
	void init() override;
	void update() override;
private:
	Transform* tr_;
};