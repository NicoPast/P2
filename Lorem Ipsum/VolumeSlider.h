#pragma once
#include "Component.h"
#include "Sprite.h"
#include "Drag.h"

class VolumeSlider : public Component
{
public:
	VolumeSlider(Transform* tr, int channel, bool horiz, int min, int max) :
		Component(ecs::VolumeSlider), tr_(tr), channel_(channel),
		horizontal_(horiz), minimum_(min), maximum_(max)
	{};
	~VolumeSlider() {};

	void init() override;
	void update() override;
	int prevVal = 0;
private:

	void setPos(int value);
	void changeVolume(int val);

protected:
	Transform* tr_ = nullptr;
	int channel_ = 0;				//canal de audio que va a controlar. 0 para la música, el resto de números para cada canal
	bool horizontal_ = true;		//si el slider está en horizontal o vertical
	int minimum_ = 0, maximum_ = 0;	//cuanto se puede mover a izquierda o derecha
	bool clicked = false;
};