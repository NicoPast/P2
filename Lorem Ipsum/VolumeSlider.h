#pragma once
#include "Component.h"
#include "Sprite.h"

class VolumeSlider : public Component
{
public:
	VolumeSlider(Transform* tr, int channel, bool horiz) :
		Component(ecs::Slider), tr_(tr), channel_(channel), horizontal_(horiz) {};
	~VolumeSlider() {};

protected:
	Transform* tr_ = nullptr;
	Sprite* spr_;
	int channel_ = 0;
	bool horizontal_ = true;
};