#pragma once
#include "Drag.h"
class Timeline;
using CallBackTL = void(Timeline*, Transform*);

class DragTL : public Drag
{
public:
	DragTL(Timeline* tl, CallBackTL* cb) : Drag(nullptr), f_(cb), tl_(tl) {};
	~DragTL() {};
	void update() override;

private:
	virtual void func() { f_(tl_); }
	CallBackTL* f_;
	Timeline* tl_;
};

