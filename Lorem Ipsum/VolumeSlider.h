#pragma once
#include "Component.h"

class VolumeSlider : public Component
{
public:
	VolumeSlider(Transform*tr, int channel);
	~VolumeSlider() {};

protected:
	Transform* tr_ = nullptr;
	int channel_ = 0;
};