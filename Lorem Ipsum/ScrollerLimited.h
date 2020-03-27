#pragma once
#include <vector>
#include "Transform.h"
#include "ecs.h"
#include "Scroller.h"

class ScrollerLimited : public Scroller
{
public:
	ScrollerLimited() {}
	virtual ~ScrollerLimited() {}
	//Igual que Scroll, pero no permite mover el primer y ultimo elemento mas lejos que el borde para que no deje espacio en blanco
	virtual void scroll(int distance);

private:
};