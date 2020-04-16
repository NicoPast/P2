#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Drag.h"
class Chinchetario;
using CallBackDD = void(Chinchetario*, Entity*);


class DragDrop : public Drag
{
public:
	DragDrop(Chinchetario* ch, CallBackDD* cb);
	~DragDrop() {};
	void update() override;
private:
	virtual void func() { f_(ch_, entity_); }
	CallBackDD* f_;
};

