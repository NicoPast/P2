#pragma once
#include "Button.h"
#include "DragDrop.h"
#include "Text.h"

using CallBackDDT = void(DragDrop* dd, Text* t);

class ButtonClue :
	public Button
{
public:
	ButtonClue(CallBackDDT f, DragDrop* dd, Text* t) : Button(), f_(f), dd_(dd), t_(t) {};
	virtual ~ButtonClue() {};
private:
	CallBackDDT* f_;
	virtual void callback() {
		f_(dd_, t_);
	}
	DragDrop* dd_; //PROVISIONAL
	Text* t_;
};

