#pragma once
#include "Button.h"
#include "DragDrop.h"
#include "Text.h"
#include "StoryManager.h"

using CallBackDDT = void(Text* t, Text* d, string newT, string newD);

class ButtonClue :
	public Button
{
public:
	ButtonClue(CallBackDDT f, Text* t, Text* description, string newT, string newD) : Button(), func_(f), title_(t), description_(description), newT_(newT), newD_(newD) {};
	virtual ~ButtonClue() {};
private:
	virtual void callback() {
		func_(title_, description_, newT_,newD_);
	}
	CallBackDDT* func_;
	string newT_;
	string newD_;
	Text* title_;
	Text* description_;
};

