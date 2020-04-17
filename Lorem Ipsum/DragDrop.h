#pragma once
#include "SDL_macros.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Drag.h"
#include "Line.h"
class Chinchetario;
using CallBackDD = void(Chinchetario*, Entity*);


class DragDrop : public Drag
{
public:
	DragDrop(Chinchetario* ch, CallBackDD* cb);
	~DragDrop() {};
	void update() override;
	void setLine(Line* l) { l_ = l; }
	void detachLine() { l_ = nullptr; }
private:
	virtual void func() { f_(ch_, entity_); }
	virtual void func2() { tr_->eliminateParent(); }
	CallBackDD* f_;
	Line* l_ = nullptr;
};

