#pragma once
#include "Component.h"
#include "Sprite.h"
#include "Drag.h"

class VolumeSlider : public Component
{
public:
	VolumeSlider(Transform* tr, int channel, bool horiz) :
		Component(ecs::Slider), tr_(tr), channel_(channel), horizontal_(horiz) {};
	~VolumeSlider() {};

	void update() override;

private:
	void moveHorizontally(Vector2D whereTo);
	void moveVertically(Vector2D whereTo);


protected:
	Transform* tr_ = nullptr;
	int channel_ = 0;				//canal de audio que va a controlar
	bool horizontal_ = true;		//si el slider está en horizontal o vertical
	int minimum_ = 0, maximum_ = 0;	//cuanto se puede mover a izquierda o derecha
};