#pragma once
#include "Drag.h"
class Timeline;
using CallBackTL = void(Timeline*, Entity*);

class DragTL : public Drag
{
public:
	DragTL(Timeline* tl, CallBackTL* cb) : Drag(nullptr), f_(cb), tl_(tl) {};
	~DragTL() {};
	void update() override;

private:
	virtual void func() { f_(tl_, entity_); }
	CallBackTL* f_= nullptr;
	Timeline* tl_ = nullptr;
};

